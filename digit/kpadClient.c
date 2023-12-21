#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>


#define FIFOFILE "fifo"

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

//int numArr[4];//입력한 번호 
char buf[BUFSIZ];
int i=0;

void typing(int num);

int main(){

	printf("Rabery Pi - key pad \n");
	wiringPiSetupGpio();

	pinMode(C1,INPUT);
	pinMode(C2,INPUT);
	pinMode(C3,INPUT);
	pinMode(C4,INPUT);
	pinMode(R1,OUTPUT);
	pinMode(R2,OUTPUT);
	pinMode(R3,OUTPUT);
	pinMode(R4,OUTPUT);

	pullUpDnControl(C1, PUD_UP);
	pullUpDnControl(C2, PUD_UP);
	pullUpDnControl(C3, PUD_UP);
	pullUpDnControl(C4, PUD_UP);

	digitalWrite(R1,HIGH);
	digitalWrite(R2,HIGH);
	digitalWrite(R3,HIGH);
	digitalWrite(R4,HIGH);

	int n, fd;
    

	if((fd=open(FIFOFILE,O_WRONLY))<0){
        perror("open()");
        return -1;
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
			}else{}

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
			}else{}
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
			}else{}
         	digitalWrite(R3,1);
			delay(50);	

			digitalWrite(R1,1);
			digitalWrite(R2,1);
			digitalWrite(R3,1);
			digitalWrite(R4,0);

			if(digitalRead(C1)==0){
				if(i%4==0){
					
				}else if(i%4==1){
					buf[i++]='*';
					buf[i++]='*';
					buf[i++]='*';
				}else if(i%4==2){
					buf[i++]='*';
					buf[i++]='*';
				}else if(i%4==3){
					buf[i++]='*';
				}
				write(fd,buf,4);
				
                //break;
			}
			else if(digitalRead(C2)==0){ // 0
                typing(8);
			}                        
			else {}
			digitalWrite(R4,1);
			delay(50);				

    }

    return 0;
}


void typing(int num){	 
	 sprintf(buf+(i++), "%d", num);
	 printf("client: %c",buf[i-1]);
	 fflush(stdout);
}

