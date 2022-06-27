#include "DHT11.c"

/* private */
static char DHT11_Get_Byte(int pin);

/* public */
char DHT11_Read(char *umidade, char *temperatura, int pin);
