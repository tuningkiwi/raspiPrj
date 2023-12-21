#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

#define FIFOFILE "fifo"
#define FLAG_OUT 5
#define FLAG_SET 0 

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
#define DIG1 18 //DIG1은 FND 왼쪽에서 1번째 자리를 의미. 
#define DIG2 23 //DIG2는 FND 왼쪽에서 2번째 자리를 의미.
#define DIG3 24 //DIG3는 FND 왼쪽에서 3번째 자리를 의미. 
#define DIG4 25 //DIG4는 FND 왼쪽에서 4번째 자리를 의미. 
#define LED_A 22 
#define LED_B 17
#define LED_C 14
#define LED_D 8
#define LED_E 5
#define LED_F 27
#define LED_G 4
#define LED_DP 15


//keypad configure input/output pin
#define C4 6	//input
#define C3 13
#define C2 19
#define C1 26
#define R1 12 //output
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
int flag =0;
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

	int num=0;
	int numDest = 0;
	int numTemp = 0;
	int count =0;
	int place = 0;
	int result =0; 
	int j = 0;

    int n, fd;
    char buf[BUFSIZ];
    //int num = 0; 
	
	//digit 세팅 
	for(int i = 0; i<4; i++){
		digitalWrite(digPin[i],0);
	}
	delay(5);

	//keypad 입력 받기 
    unlink(FIFOFILE);

    if(mkfifo(FIFOFILE, 0666)<0){
        perror("mkfifo()");
        return -1;
    }

    if((fd=open(FIFOFILE,O_RDONLY))<0){
        perror("open()");
        return -1;
    }

	while((n=read(fd,buf,4))>0){
		if(flag !=FLAG_OUT){
			numDest = atoi(buf);
			printf("iam 1\n");

		}else{
			flag = FLAG_SET;
			printf("iam 2\n");
		}
       
       	//목표층을 터미널에 출력합니다. 
		printf("YOUR DESTINATION: %d ",numDest);
		fflush(stdout);
		delay(1000); //1초뒤 출력 시작합니다. 

		/**	숫자 0 부터 차례로 count up 하여, 목표층 도달할 때 정지한다
		*	@param	num		현재 출력하는 숫자 
		*/ 
		for(int num=0; num <= numDest ;num++){
			if(flag == FLAG_OUT){break;}
			//현재의 숫자를 numTemp에 임시로 저장합니다.  
			numTemp = num;

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
					// if(read(fd,buf,4)==0){
					// 	printf("iam 3\n");
					// 	flag = FLAG_OUT;
					// 	numDest = atoi(buf);
					// 	break;
					// }
				}
			
			
			}

			count = 5;// count는 LED 출력 횟수. 이것으로 숫자 출력되는 속도를 조절할 수 있다. 
			//LED는 깜빡이는 것이 순식간이라 사람의 눈에는 착시로 계속 켜져있는 것처럼 보인다. 

			while(count--){//현재 층을 count 번 출력, 속도 조절 가능
				if(flag == FLAG_OUT){break;}
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


		}
    }


	return 0;
}


//전달 받은 num 값을  numArr에 순서대로 저장합니다. 
void typing(int num){
    numArr[numArrCnt++]=num;

}