#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <mcp3004.h>

#define BASE 100 //가상의 핀 번호 
#define SPI_CHAN 0  //실제 MCP3008 CH 번호 


int main(){
	wiringPiSetup();
	printf("RasPi SPI ADC program\n");

	mcp3004Setup(BASE, SPI_CHAN);

	while(1){
		printf("CDS: %d\n", analogRead(BASE +SPI_CHAN));
		delay(500);

	}
	return 0;
}
