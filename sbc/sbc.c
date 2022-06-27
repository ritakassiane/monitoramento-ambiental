#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <pthread.h>
#include <lcd.h>
#include <time.h>
#include <ads1115_rpi.h>
#include <mosquitto.h>
#include <string.h>
#include "DHT11.h"

//USE WIRINGPI PIN NUMBERS
#define LCD_RS  6              	//Register select pin
#define LCD_E   31             	//Enable Pin
#define LCD_D4  26              //Data pin D4
#define LCD_D5  27             	//Data pin D5
#define LCD_D6  28             	//Data pin D6
#define LCD_D7  29             	//Data pin D7
#define LED 	22		//GPIO 6
#define BUT_0	21		//GPIO 5
#define BUT_1	24		//GPIO 19
#define BUT_2	25		//GPIO 26
#define DHT11	4		//GPIO 23

//States
#define START 		0
#define MENU		1
#define HISTORIC	2
#define EDITOR		3
#define EXIT		4

//Global
int 	newMeasures[4];
char 	histDate[10][20];
int	histDataInt[10][6];
int 	histUmi[10];
int 	histTemp[10];
int 	histPress[10];
int 	histLumi[10];
int 	sTime = 6;
bool 	exitMenu = 0, exitMqtt = 0, exitSensor = 0;

void addVetor(int* vetor, int data){
	for (int i = 9; i > 0 ; i--){
		vetor[i] = vetor[i-1];
	}
	vetor[0] = data;
}

char* readData(int id){
	static char data[35];
	char strBufferUmi[3], strBufferTemp[3], strBufferPress[3], strBufferLumi[3];

        if      (histUmi[id] > 99) sprintf(strBufferUmi,   "%d", histUmi[id]);
        else if (histUmi[id] >  9) sprintf(strBufferUmi,  "0%d", histUmi[id]);
        else                      sprintf(strBufferUmi, "00%d", histUmi[id]);

        if      (histTemp[id] > 99) sprintf(strBufferTemp,   "%d", histTemp[id]);
        else if (histTemp[id] >  9) sprintf(strBufferTemp,  "0%d", histTemp[id]);
        else                       sprintf(strBufferTemp, "00%d", histTemp[id]);

        if      (histPress[id] > 99) sprintf(strBufferPress,   "%d", histPress[id]);
        else if (histPress[id] >  9) sprintf(strBufferPress,  "0%d", histPress[id]);
        else                        sprintf(strBufferPress, "00%d", histPress[id]);

        if      (histLumi[id] > 99) sprintf(strBufferLumi,   "%d", histLumi[id]);
        else if (histLumi[id] >  9) sprintf(strBufferLumi,  "0%d", histLumi[id]);
        else                        sprintf(strBufferLumi, "00%d", histLumi[id]);

	sprintf(data, "%s;%s;%s;%s;%s", histDate[id], strBufferUmi, strBufferTemp, strBufferPress, strBufferLumi);
	return data;
}

void readDHT11(){
	char humidity[2], temperature[2];
	int x = DHT11_Read(humidity, temperature, DHT11);
	if (x == 0){
		//printf("Leitura Feita =)\n");
		newMeasures[0] = (int)humidity[0];
		newMeasures[1] = (int)temperature[0];
	} else {
		//printf("Leitura Falha =)\n");
		newMeasures[0] = -1;
		newMeasures[1] = -1;
	}
}

int mqtt_pubTimer(int dado){
        int rc;
        struct mosquitto * mosq;
	char timer[4];
	sprintf(timer, "%d", dado);
        mosquitto_lib_init();

        mosq = mosquitto_new("mqttTimer", true, NULL);

        mosquitto_username_pw_set(mosq, "aluno", "aluno*123");
        rc = mosquitto_connect(mosq, "10.0.0.101", 1883, 60);

        if(rc != 0){
                printf("Cliente não se conectou ao broker: Erro %d\n", rc);
                mosquitto_destroy(mosq);
                return -1;
        }

        mosquitto_publish(mosq, NULL, "Timer", 4, timer, 0, false);

        mosquitto_disconnect(mosq);
        mosquitto_destroy(mosq);

        mosquitto_lib_cleanup();
        return 0;
}

int mqtt_pubMeasures(char * dado){
        int rc;
        struct mosquitto * mosq;

        mosquitto_lib_init();

        mosq = mosquitto_new("mqttMeasures", true, NULL);

        mosquitto_username_pw_set(mosq, "aluno", "aluno*123");
        rc = mosquitto_connect(mosq, "10.0.0.101", 1883, 60);

        if(rc != 0){
                printf("Cliente não se conectou ao broker: Erro %d\n", rc);
                mosquitto_destroy(mosq);
                return -1;
        }

        mosquitto_publish(mosq, NULL, "measuresSBC", 35, dado, 0, false);

        mosquitto_disconnect(mosq);
        mosquitto_destroy(mosq);

        mosquitto_lib_cleanup();
        return 0;
}

void on_connect(struct mosquitto *mosq, void *obj, int rc){
        if (rc){
                printf("Erro: %d\n", rc);
                exit(-1);
        }
        mosquitto_subscribe(mosq, NULL, "Timer", 0);
}

void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg){
	int buffer = atoi(msg->payload);
	if (3 > buffer) 	sTime = 3;
	if (99999 < buffer) 	sTime = 99999;
	else 			sTime = buffer;
}

void* mqtt_sub(void *arg){
        int rc, id = 310;

        mosquitto_lib_init();

        struct mosquitto *mosq;

        mosq = mosquitto_new("mqtt/Timer", true, &id);
        mosquitto_connect_callback_set(mosq, on_connect);
        mosquitto_message_callback_set(mosq, on_message);

        mosquitto_username_pw_set(mosq, "aluno", "aluno*123");
        rc = mosquitto_connect(mosq, "10.0.0.101", 1883, 60);

        if(rc){
                printf("Erro ao Sub se conectar ao broker\n");
		exitMqtt = 1;
        } else {
        	mosquitto_loop_start(mosq);
		while(!exitMenu);
	       	mosquitto_loop_stop(mosq, true);

        	mosquitto_disconnect(mosq);
		mosquitto_destroy(mosq);
		mosquitto_lib_cleanup();
		exitMqtt = 1;
	}
}


void* measure(void *arg){
        time_t t;
        struct tm tm;

	char mqttData[32];
	int lumiBuffer, pressBuffer, dateBufferInt[6];
	char dateBuffer[19];
	if(openI2CBus("/dev/i2c-1") == -1){
		printf("Sensor não está sendo lido!\n");
	}
	setI2CSlave(0x48);
	while(!exitMenu){
		lumiBuffer = readVoltage(0) *100;
		pressBuffer = readVoltage(1) *100;
		readDHT11();

		addVetor(histLumi, lumiBuffer);
		addVetor(histPress, pressBuffer);
		if (newMeasures[0] != -1) addVetor(histUmi, newMeasures[0]);
		if (newMeasures[1] != -1) addVetor(histTemp, newMeasures[1]);

		t = time(NULL);
		tm = *localtime(&t);

		sprintf(dateBuffer, "%02d/%02d/%02d;%02d:%02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
		for (int i = 9; i > 0; i--){
			strcpy(histDate[i], histDate[i-1]);
		}

		strcpy(histDate[0], dateBuffer);

		strcpy(mqttData, readData(0));
		mqtt_pubMeasures(mqttData);

		sleep(sTime);
	}
	exitSensor = 1;
}

void readHist(){
	FILE *pont_hist;
	char ArqLine[40]; //  20/06/2022;08:50:00;000;000;000;000

	pont_hist = fopen("Historico.txt","r");
	if(pont_hist == NULL) return;

	for(int i = 0; i < 10; i++){
		char bufferUmi[3], bufferTemp[3], bufferPress[3], bufferLumi[3];

		fgets(ArqLine, 40, pont_hist);

		for (int k = 0; k < 19; k++) histDate[i][k] = ArqLine[k];

		for (int k = 0; k < 3; k++){
			bufferUmi[k] = ArqLine[k + 20];
			bufferTemp[k] = ArqLine[k + 24];
			bufferPress[k] = ArqLine[k + 28];
			bufferLumi[k] = ArqLine[k + 32];
		}
		histUmi[i] = atoi(bufferUmi);
		histTemp[i] = atoi(bufferTemp);
		histPress[i] = atoi(bufferPress);
		histLumi[i] = atoi(bufferLumi);
	}

	fclose(pont_hist);
}

void saveHist(){
	FILE* pontArq = fopen("Historico.txt", "w");

	for (int i = 0; i < 10; i++) fprintf(pontArq, "%s\n", readData(i));
	fclose(pontArq);
}

void main()
{
	pthread_t sensorManeger, mqttSubManeger;
	pthread_create(&sensorManeger, NULL, measure, NULL);
	pthread_create(&mqttSubManeger, NULL, mqtt_sub, NULL);

	int lcd;
	wiringPiSetup();
	lcd = lcdInit (2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);

	char displayMenu[6][17] =	{"1 Umidade       ",
					 "2 Temperatura   ",
					 "3 Pressao       ",
					 "4 Luminosidade  ",
					 "5 Tempo De Medi.",
					 "6 Sair          "};

	char displayOptions[7][17] = 	{"       ok      >",
					 "<      ok      >",
					 "<      ok       ",
					 "       <<      >",
					 "<      <<      >",
					 "<      <<       ",
					 "+      <<      -"};

	char displayUnit[4][17] = 	{"%", " C", "atm", "lux"};
	displayUnit[1][0] = 223; // °

	int bufferTime = sTime;
	int menu = 0;
	int hist = 0;
	char bufferInt[10];
	int button = 0;
	int state = START;

	for (int i = 0; i < 10; i++){
		histUmi[i] = 0;
		histTemp[i] = 0;
		histPress[i] = 0;
		histLumi[i] = 0;
	}

	while(!exitMenu) {
		lcdClear(lcd);
        	lcdPosition(lcd, 0, 0);
		switch (state){
			case START:
				if (button != 0) state = MENU;
				else readHist();
				break;
			case MENU:
				if 	(button == 1 && menu > 0) menu--;
				else if (button == 3 && menu < 5) menu++;
				else if (button == 2){
					if 	(menu == 4) {
							    state = EDITOR;
							    bufferTime = sTime;}
					else if (menu == 5) state = EXIT;
					else	 	    state = HISTORIC;
				}
				break;
			case HISTORIC:
				if	(button == 1 && hist >  0) hist--;
				else if (button == 3 && hist < 19) hist++;
				else if (button == 2){
					state = MENU;
					hist = 0;
				}
				break;
			case EDITOR:
				if (button == 1 && bufferTime < 99999) bufferTime++;
				else if (button == 3 && bufferTime > 3) bufferTime--;
				else if	(button == 2){
					state = MENU;
					mqtt_pubTimer(bufferTime);
				}
				break;
			case EXIT:
				if (button == 1){
					saveHist();
					exitMenu = 1;
				}
				else if (button == 3) state = MENU;
				break;
		}

		switch (state){
			case START:
				lcdPuts(lcd, "MONITORAMENTO");
				lcdPosition(lcd, 0, 1);
				lcdPuts(lcd, "DE SENSORES");
				break;
			case MENU:
				lcdPosition(lcd, 0, 0);
				lcdPuts(lcd, displayMenu[menu]);
				lcdPosition(lcd, 0, 1);
				if 	(menu == 0) lcdPuts(lcd, displayOptions[0]);
				else if	(menu == 5) lcdPuts(lcd, displayOptions[2]);
				else 		    lcdPuts(lcd, displayOptions[1]);
				break;
			case HISTORIC:
				if(hist % 2){
					sprintf(bufferInt, "%d:", hist/2 + 1);
					lcdPuts(lcd, bufferInt);
					if	(menu == 0) sprintf(bufferInt, "%d", histUmi[hist/2]);
					else if (menu == 1) sprintf(bufferInt, "%d", histTemp[hist/2]);
					else if (menu == 2) sprintf(bufferInt, "%d", histPress[hist/2]);
					else if (menu == 3) sprintf(bufferInt, "%d", histLumi[hist/2]);
					lcdPuts(lcd, bufferInt);
					lcdPuts(lcd, displayUnit[menu]);
				} else if (hist == 0){
					lcdPuts(lcd, "  Medida Atual  ");
				} else {
					sprintf(bufferInt,"%d:", hist/2 +1);
					lcdPuts(lcd, bufferInt);
					for(int i = 0; i < 19; i++){
						if (i == 5){
							i = 10;
							lcdPutchar(lcd, ' ');
						} else {
							lcdPutchar(lcd, histDate[hist/2][i]);
						}
					}
				}
				lcdPosition(lcd, 0, 1);
				if 	(hist == 0) lcdPuts(lcd, displayOptions[3]);
				else if	(hist == 9) lcdPuts(lcd, displayOptions[5]);
				else 		    lcdPuts(lcd, displayOptions[4]);
				break;
			case EDITOR:
				lcdPuts(lcd, "Tempo (s): ");
				sprintf(bufferInt, "%d", bufferTime);
				lcdPuts(lcd, bufferInt);
				lcdPosition(lcd, 0, 1);
				lcdPuts(lcd, displayOptions[6]);
				break;
			case EXIT:
				lcdPosition(lcd, 0, 0);
				if (button == 1 || button == 3) lcdClear(lcd);
				else lcdPuts(lcd, "Deseja sair?    Sim          Nao");
				break;
		}

		while (button != 0 && !exitMenu) {
			if(digitalRead(BUT_0) && digitalRead(BUT_1) && digitalRead(BUT_2))
				button = 0;
		}
		delay(60);
		while (button == 0 && !exitMenu){
			if(!digitalRead(BUT_0)) button = 1;
			else if(!digitalRead(BUT_1)) button = 2;
			else if(!digitalRead(BUT_2)) button = 3;

		}
	}
	while (!exitMqtt || !exitSensor);
}
