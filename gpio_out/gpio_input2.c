#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>

#define	 INKEY1	 5
#define	INKEY2	6

int main(){
	printf("Rasberry Pi - key Input Test\n");
	wiringPiSetupGpio(); //BMC
	pinMode(INKEY1, INPUT);
	pinMode(INKEY2, INPUT);
	pinMode(21,OUTPUT);

	while(1){
		//int value = digitalRead(KEY);
		if( digitalRead(INKEY1) == LOW){
			digitalWrite(21,HIGH);
			printf("Key1 is pressed \n");
			delay(1000);
			//digitalWrite(21,LOW);
		}else if(digitalRead(INKEY2)==LOW){
			digitalWrite(21,LOW);
			printf("key2 is pressed \n");
			delay(1000);
		}

	}
	return 0;

}
