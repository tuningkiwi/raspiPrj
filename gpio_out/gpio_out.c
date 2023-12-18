#include <stdio.h>
#include <wiringPi.h>

#define LED 13

int main(){

	//wiringPiSetup();//WIRING PI 모드 사용 
	wiringPiSetupGpio();//BCM 모드 
	pinMode(LED, OUTPUT);
	int count =5;
	while(count){
		digitalWrite(LED, HIGH);
		delay(1000);
		digitalWrite(LED, LOW);
		delay(1000);
		count--;
	}

	//digitalWrite(LED,LOW);


	return 0;
}
