#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <math.h>
#include <softTone.h>
#include "lcd1602.h"

#define C4 6
#define C3 13
#define C2 19
#define C1 26
#define R1 12
#define R2 16
#define R3 20
#define R4 21
#define  pwLen  4  //PW 길이 
#define PIN_PIEZO (18)

//LED ONOFF 
// #define LED 22
#define SUCCESS 10
#define WRONG 11



const int melody[] = {131,147,165,175,196,220,247,262,293,329};
const int suc_melody[] ={261,293,329,349,392};
const int wro_melody[] ={392,349,329,293,261};

int xio;

int numArr[pwLen];//입력한 번호 
int i=0;
int num1 = 0;

char curOp = 0;
int mode =0; //0번 default -1 setting 

int pw[pwLen];//pw
int k =0;


void typing(int num);
void numPrint(int num);
void piano(int num);
//void ledOnOff(int flag);

int main(){
	printf("Rabery Pi - key pad \n");
	wiringPiSetupGpio();
	xio = wiringPiI2CSetup(I2C_ADDR);
	softToneCreate(PIN_PIEZO);

	//pinMode(LED, OUTPUT);

	pinMode(C1,INPUT);
	pinMode(C2,INPUT);
	pinMode(C3,INPUT);
	pinMode(C4,INPUT);
	pinMode(R1,OUTPUT);
	pinMode(R2,OUTPUT);
	pinMode(R3,OUTPUT);
	pinMode(R4,OUTPUT);
	//pinMode(LED,OUTPUT);
	//digitalWrite(R1,HIGH);

	pullUpDnControl(C1, PUD_UP);
	pullUpDnControl(C2, PUD_UP);
	pullUpDnControl(C3, PUD_UP);
	pullUpDnControl(C4, PUD_UP);


	digitalWrite(R1,HIGH);
	digitalWrite(R2,HIGH);
	digitalWrite(R3,HIGH);
	digitalWrite(R4,HIGH);

	//비밀번호 초기화 0000
	for(int el =0; el < pwLen; el++){
		pw[el]=0;
	}

	while(1){

        	digitalWrite(R1,0);
			digitalWrite(R2,1);
			digitalWrite(R3,1);
			digitalWrite(R4,1);

			if(digitalRead(C1)==0){ //1
                typing(1);
			}
			else if(digitalRead(C2)==0){ //2
                typing(2);
			}                        
			else if(digitalRead(C3)==0){ //3
                typing(3);
			}
         	digitalWrite(R1,1);
			delay(50);	

        	digitalWrite(R1,1);
			digitalWrite(R2,0);
			digitalWrite(R3,1);
			digitalWrite(R4,1);

			if(digitalRead(C1)==0){ //4
                typing(4);
			}
			else if(digitalRead(C2)==0){ //5
                typing(5);
			}                        
			else if(digitalRead(C3)==0){ //6
                typing(6);
			}
         	digitalWrite(R2,1);
			delay(50);	

        	digitalWrite(R1,1);
			digitalWrite(R2,1);
			digitalWrite(R3,0);
			digitalWrite(R4,1);

			if(digitalRead(C1)==0){ //7
                typing(7);
			}
			else if(digitalRead(C2)==0){ //8
                typing(8);
			}                        
			else if(digitalRead(C3)==0){ //9
                typing(9);
			}
         	digitalWrite(R3,1);
			delay(50);	

			digitalWrite(R1,1);
			digitalWrite(R2,1);
			digitalWrite(R3,1);
			digitalWrite(R4,0);

			if(digitalRead(C1)==0){ //*
				
				if(mode >=0){//default 
					
					int flag =0;
					//비번이랑 맞는지 체크 
					for(int el=0; el<pwLen; el++){
						if(pw[el]!=numArr[el]){
							flag = 1;
						}
					}
					if(flag == 1){
						printf("WRONG!");
						fflush(stdout);
						
						lcdClear();
						lcdLoc(LINE1);
						typeln("PW INPUT");
						lcdLoc(LINE2);
						typeln("WRONG!");
						
						piano(WRONG);
						

					}else {
						printf("success!\n");

						lcdClear();
						lcdLoc(LINE1);
						typeln("PW INPUT");
						lcdLoc(LINE2);
						typeln("success!");
					
						//성공하면 3초간 LED ON
						piano(SUCCESS);
						
					}
					mode =0;
					i=0;
					for(int el =0; el < pwLen; el++){
						numArr[el]=0;
					}
				}else if(mode <=-1){
					//비번 세팅 완료 
					printf("pw setting complete\n");

					lcdClear();
					lcdLoc(LINE1);
					typeln("PW SET");
					lcdLoc(LINE2);
					typeln("success!");
					piano(SUCCESS);
					k=0;
					mode =0;
				} 
                
			}
			else if(digitalRead(C2)==0){ //0
                printf("0");
				fflush(stdout);
				typing(0);
			}                        
			else if(digitalRead(C3)==0){ //#
                mode = -1;
				lcdClear();
				lcdLoc(LINE1);
				typeln("PW SET");
				lcdLoc(LINE2);
			}else if(digitalRead(C3)==0){ // /
                
			}

			digitalWrite(R4,1);
			delay(50);				


    }

    return 0;
}

void piano(int num){
	if(num ==SUCCESS){
		for(int i = 0; i <sizeof(suc_melody)/sizeof(int) ; i++){
			softToneWrite(PIN_PIEZO, suc_melody[i]);
			delay(200);
			softToneWrite(PIN_PIEZO, 0);
			delay(200);
		}
	}else if(num ==WRONG){
		for(int i = 0; i <sizeof(wro_melody)/sizeof(int) ; i++){
			softToneWrite(PIN_PIEZO, wro_melody[i]);
			delay(200);
			softToneWrite(PIN_PIEZO, 0);
			delay(200);
		}
	}else {
		softToneWrite(PIN_PIEZO, melody[num]);
		delay(200);
		softToneWrite(PIN_PIEZO, 0);
		delay(200);
	}


}


void typing(int num){
    if(mode >=0){ //0 ,1 default
        numArr[i++]=num;

        numPrint(num);
		piano(num);
    }else{ // -1, -2 pw set 
        pw[k++]=num;
        numPrint(num);
		piano(num);
    } 

}

void numPrint(int num){
	
	if(mode ==0){
        lcdClear();
		lcdLoc(LINE1);
		typeln("PW INPUT");
		lcdLoc(LINE2);
		typeChar('*');
		mode++;
	}else if(mode >0){
		typeChar('*');
    }else if(mode ==-1){//PW SET
        lcdClear();
		lcdLoc(LINE1);
		typeln("PW SET");
		lcdLoc(LINE2);
		typeChar('*');
		mode--;
    }else if(mode < -1){
		typeChar('*');

    }

}
