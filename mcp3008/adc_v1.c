#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <mcp3004.h>
#include <wiringPiI2C.h>
#include "lcd1602.h"

#define BASE 100 //가상의 핀 번호 
#define SPI_CHAN 0  //실제 MCP3008 CH 번호 

int xio;

int main(){
	xio = wiringPiI2CSetup(I2C_ADDR);
	wiringPiSetupGpio();
	printf("RasPi SPI ADC program\n");

	mcp3004Setup(BASE, SPI_CHAN);
	int value;
	while(1){
		printf("CDS: %d\n", analogRead(BASE +SPI_CHAN));
		value = analogRead(BASE+SPI_CHAN);
		lcdClear();
		lcdLoc(LINE1);
		typeln("CDS MEASUREMENT");
		lcdLoc(LINE2);
		typeInt(value);
		delay(500);

	}
	return 0;
}
