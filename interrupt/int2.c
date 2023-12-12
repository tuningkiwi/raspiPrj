#include <stdio.h>
#include <wiringPi.h>

const int pinSW = 6; 
int flag = 0;
int cnt=0;
void intPrint(void);
//void onoff(int);

int main(){

	wiringPiSetupGpio();
	pinMode(pinSW, INPUT);
	pinMode(21,OUTPUT);
	wiringPiISR(pinSW, INT_EDGE_FALLING, intPrint);
	while(1){
		if(flag) digitalWrite(21,HIGH);
		else digitalWrite(21,LOW);
	}

	return 0;
}

void intPrint(void){
	if(flag==1) flag=0;
	else flag=1;
	printf("[%d] %d\n",cnt++,flag);
	//flag =0;
}
