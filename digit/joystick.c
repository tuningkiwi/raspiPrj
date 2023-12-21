#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <mcp3004.h>

#define BASE 100
#define SPI_CHAN 0 
#define SW_PIN 5

int main(){

    wiringPiSetupGpio();
    pinMode(SW_PIN,INPUT);
    pullUpDnControl(SW_PIN,PUD_UP);

    mcp3004Setup(BASSE, SPI_CHAN);
    printf("Rasoberrt PI SPI ADC Program\n");
    int result =0;
    int val_x = 0; 
    int val_y = 0; 

    while(1){
        if(digitalRead(SW_PIN)==0){
            printf("PUSH\t");
            result = 0; 
        }else {
            printf("OFF\t");
        }

        val_x = analogRead(BASE+0);
        printf("x: %4d\t",val_x);
        val_y = analogRead(BASE+1);
        printf("y: %4d\t",val_y);

        // >>> 
        if(val_x>=1020 && val_y >=850){
            result++;
            delay(50);
        }else if(val_x <10 && val_y>=790){
            result--;
            delay(50);
        }
        printf("result: %d\n",result);
        delay(100);

    }




    return 0; 
}