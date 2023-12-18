#include <stdio.h>
#include <wiringPi.h>
#include <softTone.h>
#include <wiringPiI2C.h>
#include <softPwm.h>

#define PIN_PIEZO (18)

const int melody[] = {131,147,165,175,196,220,247,262,294};

#define C4 6
#define C3 13
#define C2 19
#define C1 26
#define R1 12
#define R2 16
#define R3 20
#define R4 21

void piano(int num);

int main(){
	wiringPiSetupGpio();
	softToneCreate(PIN_PIEZO);

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
			piano(1);
		}
		else if(digitalRead(C2)==0){ //2
			piano(2);
		}                        
		else if(digitalRead(C3)==0){ //3
			piano(3);
		}
		digitalWrite(R1,1);
		delay(50);	

		//row 2
		digitalWrite(R1,1);
		digitalWrite(R2,0);
		digitalWrite(R3,1);
		digitalWrite(R4,1);

		if(digitalRead(C1)==0){ //4
			piano(4);
		}
		else if(digitalRead(C2)==0){ //5
			piano(5);
		}                        
		else if(digitalRead(C3)==0){ //6
			piano(6);
		}
		digitalWrite(R2,1);
		delay(50);	

		digitalWrite(R1,1);
		digitalWrite(R2,1);
		digitalWrite(R3,0);
		digitalWrite(R4,1);

		if(digitalRead(C1)==0){ //4
			piano(7);
		}
		else if(digitalRead(C2)==0){ //5
			piano(8);
		}                        
		else if(digitalRead(C3)==0){ //6
			piano(9);
		}
		digitalWrite(R3,1);
		delay(50);	

	}
}

void piano(int num){
	softToneWrite(PIN_PIEZO, melody[num]);
	delay(1000);
	softToneWrite(PIN_PIEZO, 0);
	delay(1000);
}
