#include <stdio.h>
#include <mosquitto.h>
#include <stdlib.h>

int mqtt_pub(){
	int rc;
	struct mosquitto * mosq;

	mosquitto_lib_init();

	mosq = mosquitto_new("mqttTeste", true, NULL);

	mosquitto_username_pw_set(mosq, "aluno", "aluno*123");
	rc = mosquitto_connect(mosq, "10.0.0.101", 1883, 60);

	if(rc != 0){
		printf("Cliente não se conectou ao broker: Erro %d\n", rc);
		mosquitto_destroy(mosq);
		return -1;
	}
	printf("Cliente conectado\n");

	mosquitto_publish(mosq, NULL, "dado", 32, "10/00/0000;00:00;000;000;000;000", 0, false);

	mosquitto_disconnect(mosq);
	mosquitto_destroy(mosq);

	mosquitto_lib_cleanup();
	return 0;
}

void on_connect(struct mosquitto *mosq, void *obj, int rc){
	printf("ID: %d\n", * (int *) obj);
	if (rc){
		printf("Erro: %d\n", rc);
		exit(-1);
	}
	mosquitto_subscribe(mosq, NULL, "dado", 0);
}

void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg){
	printf("on_mess1\n");
	printf("Nova mensagem no topico %s: %s\n", msg->topic, (char *) msg->payload);
	printf("on _mess2\n");
}

int mqtt_sub(){
	int rc, id = 15;

	mosquitto_lib_init();

	struct mosquitto *mosq;

	mosq = mosquitto_new("mqtt/teste", true, &id);
	mosquitto_connect_callback_set(mosq, on_connect);
	mosquitto_message_callback_set(mosq, on_message);

	mosquitto_username_pw_set(mosq, "aluno", "aluno*123");
	rc = mosquitto_connect(mosq, "10.0.0.101", 1883, 60);

	if(rc){
		printf("Deu ruim");
		return -1;
	}

	mosquitto_loop_start(mosq);
	printf("Press Enter to quit...\n");
	//getchar();
	mosquitto_loop_stop(mosq, true);

	mosquitto_disconnect(mosq);
	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();
	return 0;
}

void main(){
	mqtt_sub();
	
}
