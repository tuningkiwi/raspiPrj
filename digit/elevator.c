#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>



//4digit configure output pin 
/*   
	 DIG1	DIG2   DIG3   DIG4
	|--A-| |--A-| |--A-| |--A-|
	F    B F    B F    B F    B
	|    | |    | |    | |    |
	|--G-| |--G-| |--G-| |--G-|
	E	 C E	C E	   C E	  C
	|	 | |	| |	   | |	  |
	|--D-| |--D-| |--D-| |--D-|

*/
#define DIG1 2 //DIG1은 FND 왼쪽에서 1번째 자리를 의미. 
#define DIG2 17 //DIG2는 FND 왼쪽에서 2번째 자리를 의미.
#define DIG3 27 //DIG3는 FND 왼쪽에서 3번째 자리를 의미. 
#define DIG4 25 //DIG4는 FND 왼쪽에서 4번째 자리를 의미. 
#define LED_A 3 
#define LED_B 22
#define LED_C 23
#define LED_D 15
#define LED_E 14
#define LED_F 4
#define LED_G 24
#define LED_DP 18


//keypad configure input/output pin
#define C4 6	//input
#define C3 13
#define C2 19
#define C1 26
#define R1 12 //output
#define R2 16
#define R3 20
#define R4 21

//새로운 숫자 입력값이 들어왔을 때 
#define FLAG_ON 1
#define FLAG_OFF 0

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

//digit pin
 
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

int pth_numArr[4];
int pthCnt =0;
int flag = FLAG_OFF;
pthread_mutex_t mutx;

void typing(int num);
void *keypad(void *arg);
int up(int numDest, int beforeNumDest);
int down(int numDest, int beforeNumDest);
int ledPrint(int num, int numDest, int beforeNumDest);

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


	int numDest = 0;
    int beforeNumDest = 0;

    pthread_mutex_init(&mutx,NULL);


	//digit 세팅 
	for(int i = 0; i<4; i++){
		digitalWrite(digPin[i],0);
	}
	delay(5);

    //thread keypad
    pthread_t t_id;
    if(pthread_create(&t_id, NULL, keypad,NULL)!=0){
		puts("pthread_create() error");
		return -1;
	}


    while(1){
        //파생된 keypad로부터 FLAG ON이 될때까지 기다리기  
        while(flag ==FLAG_OFF);

        //flag on 
        pthread_mutex_lock(&mutx);
        flag =FLAG_OFF;
        pthread_mutex_unlock(&mutx);
            //pth_numArr >> numArr로 이동. 
        for(int i = 0; i < pthCnt;i++){
            numArr[i] = pth_numArr[i];
            printf("%d",numArr[i]);
            fflush(stdout);
        }

        pthread_mutex_lock(&mutx);
        numArrCnt = pthCnt;
        pthCnt = 0;
        numDest = 0;
        pthread_mutex_unlock(&mutx);

        //키패드로 입력받은 값을 다시 정수형태로 변환하여, 
        //numDest에 저장합니다. 
        for(int i = 0; i<numArrCnt; i++){
            numDest += numArr[i]*pow(10,numArrCnt-1-i);
        }

        //목표층을 터미널에 출력합니다. 
        printf("YOUR DESTINATION: %d ",numDest);
        fflush(stdout);
        //delay(1000); //1초뒤 출력 시작합니다. 

        if(numDest > beforeNumDest){
            beforeNumDest = up(numDest, beforeNumDest);
        }else{
            beforeNumDest = down(numDest, beforeNumDest);
        }        
    }

	return 0;
}

int ledPrint(int num, int numDest, int beforeNumDest){
    int numTemp = num;
	int count =0;
	int place = 0;
	int result =0; 
	int j = 0;
    //현재의 숫자를 numTemp에 임시로 저장합니다.  

    /**
     * @brief  4digit이어서 최대 4자릿수 까지만 출력이 된다. 
     * @param  num 현재 출력해야할 숫자 
     * @param  place 현재 출력해야할 숫자의 자릿수. 
     * @example 현재 num이 1234이면 i가 4일 때 10^4으로 나누어야 break가 된다. 
     */
    for(int i = 0; i <5; i++){ 
        result = num/ (int)(pow(10,i)); //
        if (result ==0){
            place = i;
            break;
        }		
    }
    //place = numArrCnt;

    //numArr에 순서대로 하나씩 넣어주기
    // num: 1234 인경우 numArr[0]:1, numArr[1]:2, numArr[2]:3, numArr[3]:4
    for(int i=0 ; i<place;i++){ 
        numArr[i]=num/pow(10,place-1-i); 
        num = num % (int)(pow(10,place-1-i));
    }

    num = numTemp;//임시로 저장한 값을 num에 재저장한다. 
    

    if(num == numDest){//목표층에 도달했을 경우 
        printf("\nArrived at %d\n",num);//터미널에 도착했다는 메세지를 출력합니다. 
        while(1){//해당 숫자 출력에서 정지해야 합니다. 

            if(flag == FLAG_ON) {
                return num;
            }

            //자릿수 만큼의 반복을 시작
            //현재 숫자의 가장 큰 자릿수부터 차례로 출력
            // exam : 4자릿수이면, j는 digCode 배열을 index 3부터 0까지 순회합니다. 
            for(int j = place-1; j >= 0 ; j--){
                //digit위치의 digCode를 set
                for(int i = 0; i<4; i++){
                    digitalWrite(digPin[i],digCode[j][i]);
                }
                //해당 digit 위치에 출력해야 하는 숫자(numArr[0]~)를 통해 찾고,
                //찾은 값을 codeArr의 index로 주어서 출력합니다.  
                for(int k = 0; k< 8; k++){
                    digitalWrite(codePin[k],codeArr[numArr[place-1-j]][k]);	
                }
                //delay를 적절하게 주는 것도 중요합니다. 
                delay(5);
            }
        }
    }

    count = 5;// count는 LED 출력 횟수. 이것으로 숫자 출력되는 속도를 조절할 수 있다. 
    //LED는 깜빡이는 것이 순식간이라 사람의 눈에는 착시로 계속 켜져있는 것처럼 보인다. 

    while(count--){//현재 층을 count 번 출력, 속도 조절 가능

        //자릿수 만큼의 반복을 시작
        for(int j = place-1; j >= 0 ; j--){ 
            //digit위치의 digCode를 set
            for(int i = 0; i<4; i++){
                digitalWrite(digPin[i],digCode[j][i]);
            }
            //해당 digit 위치에 출력해야 하는 숫자(numArr[0]~)를 통해 찾고,
            //찾은 값을 codeArr의 index로 주어서 출력합니다. 
            for(int k = 0; k< 8; k++){
                digitalWrite(codePin[k],codeArr[numArr[place-1-j]][k]);	
            }
            delay(5);
        }
    }

    return num;

}

int up(int numDest, int beforeNumDest){
    int num = 0;

	/**	숫자 0 부터 차례로 count up 하여, 목표층 도달할 때 정지한다
	*	@param	num		현재 출력하는 숫자 
	*/ 
	for(num=beforeNumDest; num <= numDest ;num++){
        ledPrint(num, numDest,beforeNumDest);
        if(flag == FLAG_ON && num == numDest){
            return num;
        }
	}
}


int down(int numDest, int beforeNumDest){
    int num=0;

	/**	숫자 0 부터 차례로 count up 하여, 목표층 도달할 때 정지한다
	*	@param	num		현재 출력하는 숫자 
	*/ 
	for(num=beforeNumDest; num >= numDest ;num--){
        ledPrint(num, numDest,beforeNumDest);
        if(flag == FLAG_ON && num == numDest){
            return num;
        }
    }
}


//전달 받은 num 값을  numArr에 순서대로 저장합니다. 
void typing(int num){
    pthread_mutex_lock(&mutx);
    pth_numArr[pthCnt++]=num;
    pthread_mutex_unlock(&mutx);
    //printf("%d",pth_numArr[pthCnt-1]);

}

void *keypad(void *arg){
    printf("keypad--\n");
    
/**
  * @brief  keypad (4x4) 버튼에 숫자를 지정하여 숫자입력을 받습니다. 
  * 		R1신호를 0으로 보낼 때, 버튼을 누르면, 0의 신호가 입력핀으로 전달됩니다. 
  *  		R1,R2,R3,R4는 OUTPUT으로 출력하고 
  * 		C1,C2,C3,C4는 INPUT(PULL UP)으로 입력을 받습니다. 
  * 		R1부터 순서대로 INPUT 신호가 0으로 잡히는지 여부를 스캔합니다. 
  * @func  typing(parameter) 매개변수를 전달하여, 필요한 수행을 합니다.
  * 		이 프로그램에서는 사용자가 입력한 숫자가 차례로 numArr[]에 전달 됩니다. 		 
  * @break  R4: 0, C1 : 0 일때(*버튼을 누를 때) 사용자의 입력이 마친것으로 간주하고, while문을 탈출합니다. 
  */
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
			}else{}
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
			}else{}
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
			}else{}
         	digitalWrite(R3,1);
			delay(50);	

			//row4 	
			digitalWrite(R1,1);
			digitalWrite(R2,1);
			digitalWrite(R3,1);
			digitalWrite(R4,0);

			if(digitalRead(C1)==0){ //* 를 누르면 while문을 탈출합니다. 
                pthread_mutex_lock(&mutx);
                flag = FLAG_ON;
                pthread_mutex_unlock(&mutx);
                printf("*");
                fflush(stdout);
                //break;
			}
			else if(digitalRead(C2)==0){ //0
                typing(0);
			}else{}                        
			
         	digitalWrite(R4,1);
			delay(50);	

	}

}