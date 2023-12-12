#include <stdio.h>
#include <wiringPi.h>

#define KEY 5

int main(){
	printf("Rasberry Pi - key Input Test\n");
	wiringPiSetupGpio(); //BMC
	pinMode(KEY, INPUT);
	pinMode(21,OUTPUT);
	int value =0;
	while(1){
		//int value
		if( digitalRead(KEY) == LOW){
			if(value %2 == 0){
				digitalWrite(21,HIGH);
				value ++;
				printf("Key is pressed \n");
				delay(1000);
			}else {
				digitalWrite(21,LOW);
				value++;
				delay(1000);
			}
		}
		/*
		else {
			digitalWrite(21,LOW);
			delay(1000);
		}
		*/


	}
	return 0;
}

