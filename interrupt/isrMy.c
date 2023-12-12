#include <stdio.h>
#include <wiringPi.h>
#include <pthread.h>

// const int in1Pin =5;
// const int in2Pin =6;
const int out1Pin =20;
const int out2Pin =21;

//pthread_mutex_t mutx1, mutx2;
int cnt5_ =1;
int cnt6_ =1;
//int flag =0;


void int1Print(void);
void int2Print(void);

int main(){
	printf("begin>>");
	wiringPiSetupGpio();
    //int cnt5=0, cnt6=0;
	// pinMode(in1Pin,INPUT);
	// pinMode(in2Pin,INPUT);
	pinMode(out1Pin,OUTPUT);
	pinMode(out2Pin,OUTPUT);
    //pthread_mutex_lock(&mutx);
	if(wiringPiISR(5, INT_EDGE_FALLING, int1Print)<0){
		printf("int1 Err !!\n");
	}
	if(wiringPiISR(6, INT_EDGE_FALLING, int2Print)<0){
		printf("int2 Err !!\n");
	}
	printf("start>>");
	while(1){
		while(cnt5_==0){
            digitalWrite(out1Pin,HIGH);
            //delay(100);
        }
       while(cnt5_==1){
            digitalWrite(out1Pin,LOW);
            //delay(100);
		}
		while(cnt6_==0){
            digitalWrite(out2Pin,HIGH);
            //delay(100);
        }
        while(cnt6_==1){
            digitalWrite(out2Pin,LOW);
		}        

	}

	return 0;

}


void int1Print(){
	printf("*");
   // if(cnt5_) cnt5_=0;
   // else cnt5_= 1;
    // pthread_mutex_lock(&mutx1);
	// int1cnt++;
    // pthread_mutex_unlock(&mutx1);
	//printf("int1print..flag= %d cnt= %d",flag, int1cnt);
	
}

void int2Print(){
	//flag=6;
	printf("#");
   // if(cnt6_) cnt6_=0;
   // else cnt6_= 1;
    // pthread_mutex_lock(&mutx2);
	// int2cnt++;
    // pthread_mutex_unlock(&mutx2);
	// //printf("int2print..flag= %d cnt = %d",flag, int2cnt);
}
