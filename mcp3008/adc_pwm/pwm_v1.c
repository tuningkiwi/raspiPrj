#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

const int pinLed = 13;

int main(){
	wiringPiSetupGpio();
	softPwmCreate(pinLed, 0, 200);
	
	while(1){
		for(int i = 0; i<100; i++){
			softPwmWrite(pinLed, i);
			delay(20);
		}
		for(int i =100; i>=0; i--){
			softPwmWrite(pinLed, i);
			delay(20);
		}
		

	}

	return 0;
}
