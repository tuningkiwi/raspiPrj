#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <math.h>
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

//LED ONOFF 
#define LED 22
#define SUCCESS 1
#define WRONG 0

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
void ledOnOff(int flag);


int main(){
	printf("Rabery Pi - key pad \n");
	wiringPiSetupGpio();
	pinMode(LED, OUTPUT);
	xio = wiringPiI2CSetup(I2C_ADDR);

	pinMode(C1,INPUT);
	pinMode(C2,INPUT);
	pinMode(C3,INPUT);
	pinMode(C4,INPUT);
	pinMode(R1,OUTPUT);
	pinMode(R2,OUTPUT);
	pinMode(R3,OUTPUT);
	pinMode(R4,OUTPUT);
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

			if(digitalRead(C1)==0){ //1
                typing(4);
			}
			else if(digitalRead(C2)==0){ //2
                typing(5);
			}                        
			else if(digitalRead(C3)==0){ //3
                typing(6);
			}
         	digitalWrite(R2,1);
			delay(50);	

        	digitalWrite(R1,1);
			digitalWrite(R2,1);
			digitalWrite(R3,0);
			digitalWrite(R4,1);

			if(digitalRead(C1)==0){ //1
                typing(7);
			}
			else if(digitalRead(C2)==0){ //2
                typing(8);
			}                        
			else if(digitalRead(C3)==0){ //3
                typing(9);
			}
         	digitalWrite(R3,1);
			delay(50);	

			digitalWrite(R1,1);
			digitalWrite(R2,1);
			digitalWrite(R3,1);
			digitalWrite(R4,0);

			if(digitalRead(C1)==0){ //*
				printf("here!\n");
				if(mode >=0){//default 
					printf("2here!\n");
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
						
						ledOnOff(WRONG);
						

					}else {
						printf("success!\n");

						lcdClear();
						lcdLoc(LINE1);
						typeln("PW INPUT");
						lcdLoc(LINE2);
						typeln("success!");
					
						//성공하면 3초간 LED ON
						ledOnOff(SUCCESS);
						
					}
					mode =0;
					i=0;
					for(int el =0; el < pwLen; el++){
						numArr[el]=0;
					}
				}else if(mode <=-1){
					printf("3here!\n");
					//비번 세팅 완료 
					printf("pw setting complete\n");

					lcdClear();
					lcdLoc(LINE1);
					typeln("PW SET");
					lcdLoc(LINE2);
					typeln("success!");
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

void ledOnOff(int flag){
	if(flag ==SUCCESS){
		digitalWrite(LED, HIGH);
		delay(3000);
		digitalWrite(LED, LOW);
	}else if(flag ==WRONG){
		int cnt =3;
		while(cnt--){
			digitalWrite(LED, HIGH);
			delay(500);
			digitalWrite(LED, LOW);
			delay(500);
		}
	}
	
}


void typing(int num){
    if(mode >=0){ //0 ,1 default
        numArr[i++]=num;
        printf("%d",num);
		fflush(stdout);
        numPrint(num);
    }else{ // -1, -2 pw set 
        pw[k++]=num;
        printf("%d",num);
		fflush(stdout);
        numPrint(num);
    } 

}

void numPrint(int num){
	
	if(mode ==0){
        lcdClear();
		lcdLoc(LINE1);
		typeln("PW INPUT");
		lcdLoc(LINE2);
		typeInt(num);
		mode++;
	}else if(mode >0){
        typeInt(num);
    }else if(mode ==-1){//PW SET
        lcdClear();
		lcdLoc(LINE1);
		typeln("PW SET");
		lcdLoc(LINE2);
		typeInt(num);
		mode--;
    }else if(mode < -1){
        typeInt(num);

    }

}
