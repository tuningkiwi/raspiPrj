#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd1602.h"

int xio;

int main(){
	printf("rasberry pi LCD TEST program\b");
	wiringPiSetupGpio();
	xio = wiringPiI2CSetup(I2C_ADDR);
	int num=0;
	//char str1[100]; 
	//char str2[] ="hello world";
	while(1){

		for(int i = 1; i<13;i+=2){
		lcdClear();
		lcdLoc(LINE1);
		typeInt(i);
		//lcdLoc(LINE2);
		//typeInt(i+2);
		delay(500);
		}
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

