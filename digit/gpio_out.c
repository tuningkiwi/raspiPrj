#include <stdio.h>
#include <wiringPi.h>
#include <math.h>

#define DIG1 18
#define DIG2 23
#define DIG3 24
#define DIG4 25
#define LED_A 22
#define LED_B 17
#define LED_C 16
#define LED_D 21
#define LED_E 26
#define LED_F 27
#define LED_G 12
#define LED_DP 20

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

	//int count =5;
	int numArr[4];
	int num=0;
	int num2 = 0;
	int count =5000;
	int place = 0;
	int result =0; 
	int j = 0;

	scanf("%d",&num2);


	for(int num=num2; num >= 0 ;num--){
		num2 =num;
		//delay(100);
		printf("%d-",num);

		
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
		
		num = num2;
		count = 100;
		//delay(100);
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
