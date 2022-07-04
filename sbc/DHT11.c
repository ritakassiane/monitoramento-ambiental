/*
	DHT11.c - Humidity e Temperature Sensor library for MikroC PRO PIC
	Author: Tiago Melo
	Blog: microcontrolandos.blogspot.com.br
*/

#include <wiringPi.h>
#include <lcd.h>
#include <stdio.h>

// Realiza a leitura de 1 byte
static char DHT11_Get_Byte(int pin)
{
char i, byte = 0b0;
unsigned timeOut;

	for( i = 0b10000000; i; i = i >> 1 ) {
		timeOut = 0xFFFF;
		while(!digitalRead(pin))
			if(!--timeOut) return 0;
		delayMicroseconds(40);

		if(digitalRead(pin)){
			byte |= i;
			timeOut = 0xFFFF;
			while(digitalRead(pin))
				if(!--timeOut) return 0;
		}
    }
    return byte;
}

/*
	Realiza a leitura da umidade e da temperatura do sensor DHT11

	Parametros:
		umidade: recebe o valor da umidade relativa
		temperatura: recebe o valor da temperatura

	Retorno:
		0 - a leitura ocorreu com sucesso
		1 - houve um erro de leitura causada pela demora na recepção dos dados
		2 - houve um erro de leitura causada pelo erro no checksum
*/
char DHT11_Read (char* umidade, char* temperatura, int pin) {
	char checksum = 0;
	unsigned timeOut = 0xFFFF;

	pinMode (pin, OUTPUT);
	digitalWrite (pin, LOW);
	delay(18);

	pinMode (pin, INPUT);
	delayMicroseconds(60);

	//max 80us
	while(!digitalRead(pin))
		if(!--timeOut) return 1;
	timeOut = 0xFFFF;
	//max 80us
	while(digitalRead(pin))
		if(!--timeOut) return 1;

	umidade[0] = DHT11_Get_Byte(pin);
	umidade[1] = DHT11_Get_Byte(pin);
	temperatura[0] = DHT11_Get_Byte(pin);
	temperatura[1] = DHT11_Get_Byte(pin);
	checksum = DHT11_Get_Byte(pin);
	if((char)(umidade[0] + umidade[1] + temperatura[0] + temperatura[1]) != checksum)
		return 2;
	return 0;
}
