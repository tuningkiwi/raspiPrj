#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <math.h>

#define DIG1 18
#define DIG2 23
#define DIG3 24
#define DIG4 25
#define LED_A 22
#define LED_B 17
#define LED_C 14
#define LED_D 8
#define LED_E 5
#define LED_F 27
#define LED_G 4
#define LED_DP 15

#define C4 6
#define C3 13
#define C2 19
#define C1 26
#define R1 12
#define R2 16
#define R3 20
#define R4 21

int codePin[8]={ // a,b,c,d,e,f,g,dp
	LED_A,LED_B,LED_C,LED_D,LED_E,LED_F,LED_G,LED_DP
};

int codeArr[10][8] ={
  //{0,0,0,0,0,0,0,0}	
  // a,b,c,d,e,f,g,dp
	{0,0,0,0,0,0,1,1},// 0
	{1,0,0,1,1,1,1,1},// 1
	{0,0,1,0,0,1,0,1},// 2
	{0,0,0,0,1,1,0,1}, //3
	{1,0,0,1,1,0,0,1}, //4
	{0,1,0,0,1,0,0,1}, //5
	{0,1,0,0,0,0,0,1}, //6
	{0,0,0,1,1,0,1,1}, //7	
	{0,0,0,0,0,0,0,1}, //8	
	{0,0,0,0,1,0,0,1}, //9	
};


int digPin[4]={
	DIG1,DIG2,DIG3,DIG4
};

int digCode[4][4]={
	{0,0,0,1}, //1자릿수
	{0,0,1,0}, //2자릿수
	{0,1,0,0}, //3자릿수
	{1,0,0,0}, //4자릿수
};


int numArr[4];
int numArrCnt =0;

void typing(int num);

int main(){

	//wiringPiSetup();//WIRING PI 모드 사용 
	wiringPiSetupGpio();//BCM 모드 
	pinMode(DIG1, OUTPUT);
	pinMode(DIG2, OUTPUT);
	pinMode(DIG3, OUTPUT);
	pinMode(DIG4, OUTPUT);
	pinMode(LED_A, OUTPUT);
	pinMode(LED_B, OUTPUT);
	pinMode(LED_C, OUTPUT);
	pinMode(LED_D, OUTPUT);
	pinMode(LED_E, OUTPUT);
	pinMode(LED_F, OUTPUT);
	pinMode(LED_G, OUTPUT);
	pinMode(LED_DP, OUTPUT);

	//keypad 
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


	//int count =5;

	int num=0;
	int num2 = 0;
	int num3 = 0;
	int count =0;
	int place = 0;
	int result =0; 
	int j = 0;



	//digit 세팅 
	for(int i = 0; i<4; i++){
		digitalWrite(digPin[i],0);
	}
	delay(5);



	//숫자 입력 받기 
	while(1){
			//row1 scan
			
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

			//row2 scan
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

			//row3 scan
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

			//row4 	
			digitalWrite(R1,1);
			digitalWrite(R2,1);
			digitalWrite(R3,1);
			digitalWrite(R4,0);

			if(digitalRead(C1)==0){ //*
                break;
			}
			else if(digitalRead(C2)==0){ //0
                typing(0);
			}                        
			
         	digitalWrite(R4,1);
			delay(50);	

	}

	for(int i = 0; i<numArrCnt; i++){
		//printf("%d..",numArr[i]);
		num2 += numArr[i]*pow(10,numArrCnt-1-i);
	}

	printf("YOUR DESTINATION: %d ",num2);
	fflush(stdout);
	delay(1000);

	//scanf("%d",&num2);

	for(int num=0; num <= num2 ;num++){
		num3 = num;
		//delay(100);
		//printf("%d-",num);

		
		for(int i = 0; i <5; i++){//자릿수 확인
			result = num/ (int)(pow(10,i));
			if (result ==0){
				place = i;
				break;
			}
			
		}

		for(int i=0 ; i<place;i++){ //numArr 하나씩 넣어주기
			numArr[i]=num/pow(10,place-1-i);
			num = num % (int)(pow(10,place-1-i));
		}
		
		num = num3;
		count = 10;
		//delay(100);

		if(num == num2){
			printf("\nArrived at %d\n",num);
			while(1){

				for(int j = place-1; j >= 0 ; j--){
				//digit 세팅 
				for(int i = 0; i<4; i++){
					digitalWrite(digPin[i],digCode[j][i]);
				}
				//첫번째로 입력한 숫자를 표시 
				for(int k = 0; k< 8; k++){
					digitalWrite(codePin[k],codeArr[numArr[place-1-j]][k]);	
				}
				delay(5);

				}
			}

		}

		while(count--){

			for(int j = place-1; j >= 0 ; j--){
				//digit 세팅 
				for(int i = 0; i<4; i++){
					digitalWrite(digPin[i],digCode[j][i]);
				}
				//첫번째로 입력한 숫자를 표시 
				for(int k = 0; k< 8; k++){
					digitalWrite(codePin[k],codeArr[numArr[place-1-j]][k]);	
				}
				delay(5);

			}
		}



	}

	return 0;
}


void typing(int num){
    numArr[numArrCnt++]=num;

}