/* 
* robocar_ll.h
*
* robocar low level board support drivers
*
* Created: 1/18/2015 11:54:25 AM
* Author: ensylam
*/


#ifndef __ROBOCAR_LL_H__
#define __ROBOCAR_LL_H__

void delay(void);				//8 clk = 723 ns (11.0592 MHz)
void delayU(unsigned char t);
char mirror(char c);			// abcdefgh -> hgfedcba


namespace LL
{
	enum HC541 {BUTTONS=0b10001100, FRONT=0b11001100, MIDDLE=0b11101100, BACK=0b10101100};
	enum HC574 {U4=0b01000000, U5=0b01100000};
	void lcdWriteNibble(unsigned char n, unsigned char c); 	//require lower nibble of n = 0
	void lcdWriteByte(unsigned char b, unsigned char c);
	char lcdReadByte(unsigned char c);
	char read541(HC541 address, unsigned char t);	//t = delay in micro-second
													//BUTTONS -> 1 us
													//MIDDLE  -> 30 us
	void write574(HC574 address, char c);
	void power(char);		//0 = off; 1 = on
	void servoSetAddress(char c);
	void frontMotorControl(char c);
	void backMotorControl(char c);
	void LED(char);	
} //namespace LL

#endif //__ROBOCAR_LL_H__
