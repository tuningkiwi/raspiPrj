#include <stdio.h>
#include <wiringPi.h>

#define LED 5

int main(){

	//wiringPiSetup();//WIRING PI 모드 사용 
	wiringPiSetupGpio();//BCM 모드 
	pinMode(LED, OUTPUT);
	//int count =5;
	while(1){
		digitalWrite(LED, HIGH);
		printf("ON\n");
		fflush(stdout);
		delay(1000);
		digitalWrite(LED, LOW);
		printf("OFF\n");
		fflush(stdout);
		delay(1000);
		//count--;
	}

	//digitalWrite(LED,LOW);


	return 0;
}
