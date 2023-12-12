#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd1602.h"

int xio;

//hc-sr04 variable
const int pinEcho = 1;
const int pinTrigger =0;


int main(){
	//hc-sr04 
	wiringPiSetupGpio();
	pinMode(pinEcho, INPUT);
	pinMode(pinTrigger, OUTPUT);
	digitalWrite(pinTrigger, LOW);
	delay(10);


	//lcd config
	printf("rasberry pi LCD TEST program\b");
	wiringPiSetupGpio();
	xio = wiringPiI2CSetup(I2C_ADDR);

	char str1[]="hello world";
	char str2[] ="LCD TEST!";
	while(1){
		digitalWrite(pinTrigger, HIGH);
		delayMicroseconds(15);
		digitalWrite(pinTrigger, LOW);

		while(digitalRead(pinEcho) == LOW);

		long startTime = micros();
		while(digitalRead(pinEcho) == HIGH);
		long endTime = micros()- startTime;
		int distance = endTime/58;
		delay(500);
		lcdClear();
		lcdLoc(LINE1);
		typeFloat(distance);
		
		/*
		lcdLoc(LINE2);
		typeln("in C not python");
		delay(2000);

		lcdClear();
		lcdLoc(LINE1);
		typeln(str1);
		lcdLoc(LINE2);
		typeln(str2);
		delay(2000);
		*/
	}

	return 0;
}


/*
void typeFloat(float myFloat){
		char buffer[20];
		sprintf(buffer, "%4.2f", myFloat);
		typeln(buffer);
}

void typeInt(int i){
	char array[20];
	sprintf(array, "%d", i);
	typeln(array);
}

void lcdClear(void){
	lcd_byte(0x01, LCD_CMD);
	lcd_byte(0x02, LCD_CMD);
}

void lcdLoc(int line){

	lcd_byte(line, LCD_CMD);
}

void typeChar(char val){
	lcd_byte(val, LCD_CHR);
}

void typeln(const char*s){
	while(*s) lcd_byte(*(s++), LCD_CHR);
}

void lcd_byte(int bits, int mode){
	int bits_high;
	int bits_low;
	bits_high = mode | (bits& 0xF0) |LCD_BACKLIGHT;
	bits_low = mode | ((bits<<4) & 0xF0) | LCD_BACKLIGHT;

	wiringPiI2CReadReg8(xio, bits_high);
	lcd_toggle_enable(bits_high);

	wiringPiI2CReadReg8(xio,bits_low);
	lcd_toggle_enable(bits_low);
}

void lcd_toggle_enable(int bits){
	delayMicroseconds(500);
	wiringPiI2CReadReg8(xio, (bits|ENABLE));
	delayMicroseconds(500);
	wiringPiI2CReadReg8(xio,(bits& ~ENABLE));
	delayMicroseconds(50);
}

void lcd_init(){
	lcd_
/*
void typeFloat(float myFloat){
		char buffer[20];
		sprintf(buffer, "%4.2f", myFloat);
		typeln(buffer);
}

void typeInt(int i){
	char array[20];
	sprintf(array, "%d", i);
	typeln(array);
}

void lcdClear(void){
	lcd_byte(0x01, LCD_CMD);
	lcd_byte(0x02, LCD_CMD);
}

void lcdLoc(int line){

	lcd_byte(line, LCD_CMD);
}

void typeChar(char val){
	lcd_byte(val, LCD_CHR);
}

void typeln(const char*s){
	while(*s) lcd_byte(*(s++), LCD_CHR);
}

void lcd_byte(int bits, int mode){
	int bits_high;
	int bits_low;
	bits_high = mode | (bits& 0xF0) |LCD_BACKLIGHT;
	bits_low = mode | ((bits<<4) & 0xF0) | LCD_BACKLIGHT;

	wiringPiI2CReadReg8(xio, bits_high);
	lcd_toggle_enable(bits_high);

	wiringPiI2CReadReg8(xio,bits_low);
	lcd_toggle_enable(bits_low);
}

void lcd_toggle_enable(int bits){
	delayMicroseconds(500);
	wiringPiI2CReadReg8(xio, (bits|ENABLE));
	delayMicroseconds(500);
	wiringPiI2CReadReg8(xio,(bits& ~ENABLE));
	delayMicroseconds(50);
}

void lcd_init(){
	lcd_byte(0x33, LCD_CMD);
	lcd_byte(0x32, LCD_CMD);
	lcd_byte(0x06, LCD_CMD);
	lcd_byte(0x0C, LCD_CMD);
	lcd_byte(0x28, LCD_CMD);
	lcd_byte(0x01, LCD_CMD);
	delayMicroseconds(500);
}
*/

