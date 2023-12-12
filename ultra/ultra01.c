#include <stdio.h>
#include <wiringPi.h>

const int pinEcho = 1;
const int pinTrigger = 0;

int main(){
	//printf("s");
	wiringPiSetupGpio();
	pinMode(pinEcho, INPUT);
	pinMode(pinTrigger,OUTPUT);
	digitalWrite(pinTrigger, LOW);
	delay(10);
	
	while(1){
		digitalWrite(pinTrigger, HIGH);
		delayMicroseconds(15);
		digitalWrite(pinTrigger, LOW);

		while(digitalRead(pinEcho) == LOW);

		long startTime = micros();
		while(digitalRead(pinEcho) == HIGH);
		long endTime = micros() - startTime;
		int distance = endTime/58;

		printf("Distance: %d\n", distance);
		if(distance > 20){
			digitalWrite(20,HIGH);
			digitalWrite(21,LOW);
		}else if(distance > 10 && distance <20){
			digitalWrite(21,HIGH);
			digitalWrite(20,LOW);
		}else if(distance <10){
			digitalWrite(20,HIGH);
			digitalWrite(21,HIGH);
		}
		delay(500);
	}
	return 0;
}

