#include <stdio.h>
#include <wiringPi.h>

const int pinSW = 6; 
int flag = 0;
int cnt =0;

void intPrint(void);

int main(){

	wiringPiSetupGpio();
	pinMode(pinSW, INPUT);
	wiringPiISR(pinSW, INT_EDGE_FALLING, intPrint);
	while(1){

	}

	return 0;
}

void intPrint(void){
	cnt++;
	printf("[%d]\n",cnt);
	//flag =0;
}
