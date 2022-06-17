#include<stdio.h>
#include<stdlib.h>
#include <time.h>
int global = 1;


void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
  
    // Storing start time
    clock_t start_time = clock();
  
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

void func(int new){ 
    global=new; 
    printf("Changed! --> %d\n", global); 
} 

int main(int value)
{
    int i;
    printf("value: %d \n", value);
    for (i = 0; i < 10; i++) {
        delay(3);
        printf("global: %d \n", global);
        func(value);
        printf("global: %d \n", global);
        // printf("%d seconds have passed\n", i + 1);
    }
    return 0;
}