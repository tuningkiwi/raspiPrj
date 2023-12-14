#include <stdio.h>
#include <wiringPi.h>
#include <math.h>

#define C4 6
#define C3 13
#define C2 19
#define C1 26
#define R1 12
#define R2 16
#define R3 20
#define R4 21

int main(){
	printf("Rabery Pi - key pad \n");
	wiringPiSetupGpio();
	//input pullUp
//	pullUpDnControl(C1, PUD_UP);
//	pullUpDnControl(C2, PUD_UP);
//	pullUpDnControl(C3, PUD_UP);/
//	pullUpDnControl(C4, PUD_UP);
	//pullUpDnControl(R1, PUD_DOWN); //출력은 pull업다운 관계없음
	
	
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

	int num1 = 0;
	int num2 = 0;
	int numArr[30];
	//char operator[4]={'+','-','*','/'};
	char curOp = 0;
	int i=0;
	while(1){


			//R1에서 실행  
			digitalWrite(R1,0);
			digitalWrite(R2,1);
			digitalWrite(R3,1);
			digitalWrite(R4,1);
			
			if(digitalRead(C1)==0){
				printf("1\n");
				numArr[i++]=1;
			}
			if(digitalRead(C2)==0)
			{	printf("2\n");
				numArr[i++]=2;

			}
			if(digitalRead(C3)==0)
			{	printf("3\n");
				numArr[i++]=3;

			}
			if(digitalRead(C4)==0)
			{	printf("+\n");
				for(int k=i-1,  m=0; k>=0;k--,m++){
					num1 += (numArr[m])*(pow(10,k));
				}
				i=0;
				//num1 = *numArr;
				curOp = '+';
			}
			digitalWrite(R1,1);
			delay(100);

			//R2에서 실행
			digitalWrite(R1,1);
			digitalWrite(R2,0);
			digitalWrite(R3,1);
			digitalWrite(R4,1);
			
			if(digitalRead(C1)==0){
				printf("4\n");
				numArr[i++]=4;
			}
			if(digitalRead(C2)==0){
				printf("5\n");
				numArr[i++]=5;
			}
			if(digitalRead(C3)==0)
			{	printf("6\n");
				numArr[i++]=6;
			}
			if(digitalRead(C4)==0)
			{	printf("-\n");
				for(int k=i-1,  m=0; k>=0;k--,m++){
					num1 += (*(numArr+(m)))*(pow(10,k));
				}
				i=0;
				curOp = '-';
			}
			
			digitalWrite(R2,1);
			delay(100);

			//R3에서 실행
			digitalWrite(R1,1);
			digitalWrite(R2,1);
			digitalWrite(R3,0);
			digitalWrite(R4,1);
			
			if(digitalRead(C1)==0){
				printf("7\n");
				numArr[i++]=7;
			}
			if(digitalRead(C2)==0){
				printf("8\n");
				numArr[i++]=8;
			}
			if(digitalRead(C3)==0){
				printf("9\n");
				numArr[i++]=9;
			}
			if(digitalRead(C4)==0)
			{	printf("*\n");
				for(int k=i-1,  m=0; k>=0;k--,m++){
					num1 += (*(numArr+(m)))*(pow(10,k));
				}
				i=0;
				curOp = '*';
			}

			digitalWrite(R3,1);
			delay(100);

			//R4에서 실행
			digitalWrite(R1,1);
			digitalWrite(R2,1);
			digitalWrite(R3,1);
			digitalWrite(R4,0);
			
			if(digitalRead(C1)==0){
				printf("=\n");
				for(int k = i-1, m=0; k>=0; k--,m++){
					num2 +=numArr[m]*(pow(10,k));
				}
				i=0;
				//num2 = *(numArr+1);
				switch(curOp){
					case '+' : printf(">> %d\n",num1+num2); break;
					case '-' : printf(">> %d\n",num1-num2); break;
					case '*' : printf(">> %d\n",num1*num2); break;
					case '/' : printf(">> %d\n",num1/num2); break;
					default : break;
				}
				for(int j=0; j<10; j++){//numArr buffer clear
					numArr[j]=0;
				}
				num1 = 0;
				num2 =0;
			
			}
			if(digitalRead(C2)==0){
				printf("0\n");
				numArr[i++]=0;
			}
			if(digitalRead(C3)==0)
				printf("#\n");
			if(digitalRead(C4)==0)
			{	printf("/\n");
				for(int k=i-1,  m=0; k>=0;k--,m++){
					num1 += (*(numArr+(m)))*(pow(10,k));
				}
				i=0;
			
				curOp = '/';
			}
			digitalWrite(R4,1);
			delay(100);

	}

	return 0;
}
