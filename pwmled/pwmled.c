#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>


void ledPwmControl(int gpio){
	pinMode(gpio, OUTPUT);
	softPwmCreate(gpio,0,200); //pwm 의 범위 설정
	int num = 0;
	while(1){
		while(num <= 200){
			softPwmWrite(gpio,num++);
			delay(20);
		}
		while(num > 0){
			softPwmWrite(gpio,num--);
			delay(20);
		}
	}
/*
	for(int i=0; i < 10000; i++){
		softPwmWrite(gpio, i&255);
		delay(5);
	}
*/
	//softPwmWrite(gpio, 0);

}

int main(int argc, char** argv){
	int gno;

	if(argc <2){
		printf("Usage: %s GPIO_NO\n", argv[0]);
		return -1;
	}

	gno = atoi(argv[1]);
	wiringPiSetupGpio();
	ledPwmControl(gno);

	return 0;

}
