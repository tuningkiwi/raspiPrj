#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <wiringPiI2C.h>

#define C4 6
#define C3 13
#define C2 19
#define C1 26
#define R1 12
#define R2 16
#define R3 20
#define R4 21

//LED ONOFF 
#define LED 23
#define SUCCESS 1
#define WRONG 0


//const int pinLed = 13;//led out pin


//int numArr[pwLen];//입력한 번호 
//int i=0;
//int num = 0;
void pwmLED(int num);

int main(){
	wiringPiSetupGpio();
	pinMode(LED, OUTPUT);
	softPwmCreate(LED, 0, 100);

	pinMode(C1,INPUT);
	pinMode(C2,INPUT);
	pinMode(C3,INPUT);
	pinMode(C4,INPUT);
	pinMode(R1,OUTPUT);
	pinMode(R2,OUTPUT);
	pinMode(R3,OUTPUT);
	pinMode(R4,OUTPUT);

	pullUpDnControl(C1, PUD_UP);
	pullUpDnControl(C2, PUD_UP);
	pullUpDnControl(C3, PUD_UP);
	pullUpDnControl(C4, PUD_UP);


	digitalWrite(R1,HIGH);
	digitalWrite(R2,HIGH);
	digitalWrite(R3,HIGH);
	digitalWrite(R4,HIGH);
	
	while(1){

		//row 1 
		digitalWrite(R1,0);
		digitalWrite(R2,1);
		digitalWrite(R3,1);
		digitalWrite(R4,1);

		if(digitalRead(C1)==0){ //1
			pwmLED(1);
		}
		else if(digitalRead(C2)==0){ //2
			pwmLED(2);
		}                        
		else if(digitalRead(C3)==0){ //3
			pwmLED(3);
		}
		digitalWrite(R1,1);
		delay(50);	

		//row 2
		digitalWrite(R1,1);
		digitalWrite(R2,0);
		digitalWrite(R3,1);
		digitalWrite(R4,1);

		if(digitalRead(C1)==0){ //4
			pwmLED(4);
		}
		else if(digitalRead(C2)==0){ //5
			pwmLED(5);
		}                        
		else if(digitalRead(C3)==0){ //6
			pwmLED(6);
		}
		digitalWrite(R2,1);
		delay(50);	
		



	}

	return 0;
}

void pwmLED(int num){
int cnt = 3;
while(cnt--){
	for(int i = 0; i<num*20; i++){
		softPwmWrite(LED, i);
		delay(20);
	}

	for(int i =num*20; i>=0; i--){
		softPwmWrite(LED, i);
		delay(20);
	}
}

}
