#include <stdio.h>
#include <wiringPi.h>

const int in1Pin =5;
const int in2Pin =6;
const int out1Pin =20;
const int out2Pin =21;
int int1cnt =0;
int int2cnt =0;
int flag =0;

void int1Print(void);
void int2Print(void);

int main(){
	printf("begin>>");
	wiringPiSetupGpio();
	pinMode(in1Pin,INPUT);
	pinMode(in2Pin,INPUT);
	pinMode(out1Pin,OUTPUT);
	pinMode(out2Pin,OUTPUT);
	if(wiringPiISR(in1Pin, INT_EDGE_FALLING, int1Print)<0){
		printf("int1 Err !!\n");
	}
	if(wiringPiISR(in2Pin, INT_EDGE_FALLING, int2Print)<0){
		printf("int2 Err !!\n");
	}
	printf("start>>");
	while(1){
		
		while(flag ==5){
			//printf("*");
			if((int1cnt %2) ==0){
				digitalWrite(out1Pin,HIGH);
				//delay(1000);
			}else {
				digitalWrite(out1Pin,LOW);
				//delay(1000);
			}
		}

		while(flag==6){
			//printf("#");
			if((int2cnt %2) ==0){
				digitalWrite(out2Pin,HIGH);
				//delay(1000);
			}else {
				digitalWrite(out2Pin,LOW);
				//delay(1000);
			}
		}
	}

	return 0;

}


void int1Print(){
	flag=5;
	int1cnt++;
	printf("5*%d",int1cnt);
	
}

void int2Print(){
	flag=6;
	int2cnt++;
	printf("6*%d", int2cnt);
}
