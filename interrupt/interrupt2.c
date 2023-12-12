#include <stdio.h>
#include <wiringPi.h>

const int pinSW = 6; 
int flag = 1;
int cnt=0;

void intPrint(void);

int main(){

	wiringPiSetupGpio();
	pinMode(pinSW, INPUT);
	//pinMode(21,OUTPUT);
	wiringPiISR(pinSW, INT_EDGE_FALLING, intPrint);
	while(1){
	/*
		if(flag) {
			digitalWrite(21,HIGH);
			//printf("*");
			delay(1000);
		}
		else {
			digitalWrite(21,LOW);
			//printf("#");
			delay(1000);
		}
	*/
	}

	return 0;
}

void intPrint(void){
	//if(flag) flag =0;
	//else flag =1;
	cnt++;
	printf("%d",cnt);
	//flag =0;
}
