#include <stdio.h>
#include <wiringPi.h>
#include <softTone.h>

#define PIN_PIEZO (18)

const int melody[] = {131,147,165,175,196,220,247,262};

int main(){
	wiringPiSetupGpio();
	softToneCreate(PIN_PIEZO);

	while(1){
		for(int i=0; i<8; i++){
			softToneWrite(PIN_PIEZO, melody[i]);
			delay(1000);
		}

		softToneWrite(PIN_PIEZO, 0);
		delay(1000);
	}
}
