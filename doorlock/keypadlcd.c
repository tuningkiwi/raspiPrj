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

int xio;

void numPrint(int*, int);
void opPrint(int*, char);

int main(){
	printf("Rabery Pi - key pad \n");
	wiringPiSetupGpio();
	xio = wiringPiI2CSetup(I2C_ADDR);

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

	int num1 = 0;
	int num2 = 0;
	int numArr[30];
	//char operator[4]={'+','-','*','/'};
	char curOp = 0;
	int i=0;
	int cals =0;
	int* calID =&cals;

	//pw set var
	int pw[4];
	//int sharp =0;
	int k =0;

	while(1){

			//R1에서 실행  
			digitalWrite(R1,0);
			digitalWrite(R2,1);
			digitalWrite(R3,1);
			digitalWrite(R4,1);
			
			if(digitalRead(C1)==0){
				if(cals <= -1){//sharp on 
					pw[k++]=1;
				}else{
					numArr[i++]=1;
				}
				numPrint(calID,1);

			}
			if(digitalRead(C2)==0)
			{	
				if(cals <= -1){//sharp on 
					pw[k++]=2;
				}else{
					numArr[i++]=2;
				}
				numPrint(calID,2);
			}
			if(digitalRead(C3)==0)
			{	
				if(cals <= -1){//sharp on 
					pw[k++]=3;
				}else{
					numArr[i++]=3;
				}
				numPrint(calID,3);
			}
			if(digitalRead(C4)==0)
			{	printf("+\n");
				for(int k=i-1,  m=0; k>=0;k--,m++){
					num1 += (numArr[m])*(pow(10,k));
				}
				i=0;
				//num1 = *numArr;
				curOp = '+';
				opPrint(calID,curOp);
			}
			digitalWrite(R1,1);
			delay(50);

			//R2에서 실행
			digitalWrite(R1,1);
			digitalWrite(R2,0);
			digitalWrite(R3,1);
			digitalWrite(R4,1);
			
			if(digitalRead(C1)==0){
				if(cals <= -1){//sharp on 
					pw[k++]=4;
				}else{
					numArr[i++]=4;
				}
				numPrint(calID,4);
			}
			if(digitalRead(C2)==0){
				if(cals <= -1){//sharp on 
					pw[k++]=5;
				}else{
					numArr[i++]=5;
				}
				numPrint(calID,5);
			}
			if(digitalRead(C3)==0)
			{	//printf("6\n");
				if(cals <= -1){//sharp on 
					pw[k++]=6;
				}else{
					numArr[i++]=6;
				}
				numPrint(calID,6);
			}
			if(digitalRead(C4)==0)
			{	printf("-\n");
				for(int k=i-1,  m=0; k>=0;k--,m++){
					num1 += (numArr[m])*(pow(10,k));
				}
				i=0;
				curOp = '-';
				opPrint(calID, curOp);
			}
			
			digitalWrite(R2,1);
			delay(50);

			//R3에서 실행
			digitalWrite(R1,1);
			digitalWrite(R2,1);
			digitalWrite(R3,0);
			digitalWrite(R4,1);
			
			if(digitalRead(C1)==0){
				//printf("7\n");
				if(cals <= -1){//sharp on 
					pw[k++]=7;
				}else{
					numArr[i++]=7;
				}
				numPrint(calID,7);
			}
			if(digitalRead(C2)==0){
				//printf("8\n");
				if(cals <= -1){//sharp on 
					pw[k++]=8;
				}else{
					numArr[i++]=8;
				}
				numPrint(calID,8);
			}
			if(digitalRead(C3)==0){
				//printf("9\n");
				if(cals <= -1){//sharp on 
					pw[k++]=9;
				}else{
					numArr[i++]=9;
				}
				numPrint(calID,9);
			}
			if(digitalRead(C4)==0)
			{	printf("*\n");
				for(int k=i-1,  m=0; k>=0;k--,m++){
					num1 += (numArr[m])*(pow(10,k));
				}
				i=0;
				curOp = '*';
				opPrint(calID,curOp);
			}

			digitalWrite(R3,1);
			delay(50);

			//R4에서 실행
			digitalWrite(R1,1);
			digitalWrite(R2,1);
			digitalWrite(R3,1);
			digitalWrite(R4,0);

			if(digitalRead(C1)==0){
				//printf("=\n");
				for(int k = i-1, m=0; k>=0; k--,m++){
					num2 +=numArr[m]*(pow(10,k));
				}
				opPrint(calID,'=');
				i=0;
				switch(curOp){
					case '+' : printf(">> %d\n",num1+num2); numPrint(calID,num1+num2); break;
					case '-' : printf(">> %d\n",num1-num2); numPrint(calID,num1-num2); break;
					case '*' : printf(">> %d\n",num1*num2); numPrint(calID,num1*num2); break;
					case '/' : {
						if(num2==0){
							lcdClear();
							lcdLoc(LINE1);
							typeln("Tuningkiwi cal");
							lcdLoc(LINE2);
							typeln("Can't be divided");
						}else {
							printf(">> %d\n",num1/num2); numPrint(calID,num1/num2); break;

						}
					}
					default : break;
				}
				for(int j=0; j<10; j++){//numArr buffer clear
					numArr[j]=0;
				}
				num1 = 0;
				num2 =0;
				cals =0;
			
			}
			if(digitalRead(C2)==0){
				//printf("0\n");
				if(cals <= -1){//
					pw[k++]=0;
				}else{
					numArr[i++]=0;
				}
				numPrint(calID,0);
			}
			if(digitalRead(C3)==0){
				//printf("#\n");
				if(cals ==0){//pw 모드로 변환 
					cals = -1;
					opPrint(calID,'#');
				}else if(cals == -2){	//pw set 마무리 
					opPrint(calID,'#');
					cals =0;//기본 모드(cal)로 back
				}
			}
			if(digitalRead(C4)==0)
			{	printf("/\n");
					
				for(int k=i-1,  m=0; k>=0;k--,m++){
					num1 += (numArr[m])*(pow(10,k));
				}
				i=0;
			
				curOp = '/';
				opPrint(calID,curOp);
			}
			digitalWrite(R4,1);
			delay(50);

	}

	return 0;
}


void numPrint(int* calID, int num){
	
	if(*calID==0){
		lcdClear();
		lcdLoc(LINE1);
		typeln("TUNINGKIWI CAL");
		lcdLoc(LINE2);
		typeInt(num);
		(*calID)++;
	}else if(*calID>=1){
		typeInt(num);
	}else if(*calID == -2){//PW MODE 
		typeInt(num);
	}

}

void opPrint(int* calID, char ch){
	if(ch == '#'&& *calID==-1){ //PW SET START
		lcdClear();
		lcdLoc(LINE1);
		typeln("DOOR PW SET");
		lcdLoc(LINE2);
		typeChar(ch);
		(*calID)--;		
	}else if(ch =='#' && *calID==-2){//PW SET END
		lcdClear();
		lcdLoc(LINE1);
		typeln("DOOR PW SET");
		lcdLoc(LINE2);
		typeln("SUCCESS");
	}else typeChar(ch);
}
