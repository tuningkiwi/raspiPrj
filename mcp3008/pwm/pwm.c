#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>


#define LED 23

int main(){
	wiringPiSetupGpio();
	pinMode(LED, OUTPUT);
	softPwmCreate(LED, 0,200);

	for(int i =0; i < 200; i++){
		softPwmWrite(LED, i);
		delay(20);
	}
	for(int i =200; i >= 0 ; i--){
		softPwmWrite(LED, i);
		delay(20);
	}


}
