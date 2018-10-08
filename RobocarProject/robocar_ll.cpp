/* 
* robocar_ll.cpp
*
* robocar low level board support drivers
*
* Created: 1/18/2015 11:54:25 AM
* Author: ensylam
*/


#include <avr/io.h>

#include "robocar_ll.h"

void __attribute__((noinline, naked)) delay(void){__asm__("ret"::);}
		//8 clk = 723 ns (11.0592 MHz)

void delayU(unsigned char t){while (t--) {delay();}}

char mirror(char c){			// abcdefgh -> hgfedcba
	__asm__ __volatile__(\
	"mov __tmp_reg__, %0" "\n\t"\
	"ldi %0, 0xfe" "\n\t"\
	"1: lsr __tmp_reg__" "\n\t"\
	"rol %0" "\n\t"\
	"brcs 1b" "\n\t"\
	:"=a" (c)\
	:"0" (c)\
	);
	return c;
}

#define LCDSTROBE() PORTA |= _BV(7); delay(); PORTA &= ~_BV(7)	//first make porta7 to be 1, after delay, porta7 becomes 0
#define BREAD		0x0F    //0b00001111
#define BWRITE		0xFF    //0b11111111
#define BUS(X)		DDRC = X	//determine whether the portc is input or output
#define BUSREAD(X)	X = PINC	//get data from portc
#define BUSWRITE(X)	PORTC = X	//set data to portc
#define BGATEH()	PORTB |= _BV(2)//make portb bit2 to be 1
#define BGATEL()	PORTB &= ~_BV(2)//make portb bit2 to be 0

#define SPICLKH()	UCSR1C |= _BV(0)	//clock polarity 
#define SPICLKL()	UCSR1C &= ~_BV(0)

#define POWERUP() PORTA |= _BV(1)	//set porta1 to 1 to give power to the car
#define POWEROFF() PORTA &= ~_BV(1)	//set porta1 to 0 to stop the car

#define LEDON() PORTA |= _BV(2)	//set porta2 to 1 to lighten the LCD
#define LEDOFF() PORTA &= ~_BV(2)	//set porta2 to 0 to power off the LCD


void __attribute__((section(".init3"), naked)) __hardwareInit(void)
{
	DDRA |= _BV(1);		// POWER
	DDRA |= _BV(2);		// LED
	DDRA |= _BV(7);		// LCD strobe
	DDRB |= _BV(2);		// HC138 GATE

	//SPI init (USART1 in MSPIM)
	DDRD |= _BV(3);			// TXD1 output
	DDRD |= _BV(4);			// XCLK1 output
	UBRR1 = 0;
	UCSR1C = 0b11000011;	// MSPIM, MSB first, idle high (write)
	UCSR1B = 0x18;			// enable transmitter and receiver
	UBRR1 = 0;				// set clock to fosc/2

	LL::write574(LL::U4, 0);
	LL::write574(LL::U5, 0);
}

void __attribute__((section(".init8"), naked)) __power(void) {POWERUP();}


namespace
{
	
char u4, u5;
	
char SPI(char c){
	while (!(UCSR1A & _BV(UDRE1)));		// wait for empty transmit buffer
	UDR1 = c;
	while (!(UCSR1A & _BV(RXC1)));		// wait for data to be received
	return UDR1;							// dummy read
}	//show the sensor's one bit

} //namespace


namespace LL
{
	
void lcdWriteNibble(unsigned char n, unsigned char c){
	// require lower nibble of n = 0
	BGATEL();
	BUS(BWRITE); BUSWRITE(n | c << 2); LCDSTROBE();
}

void lcdWriteByte(unsigned char b, unsigned char c){
	lcdWriteNibble(b & 0xf0, c);		// high nibble first,make the last 4 bits of b become 0
	lcdWriteNibble(b << 4, c);
}

char lcdReadByte(unsigned char c){
	unsigned char lownibble;
	BGATEL();	//make portb bit2 to be 0
	BUS(BREAD);	//DDRC=0b00001111
	 BUSWRITE((c | 2) << 2);	//make portc3 becomes 1
	  LCDSTROBE();	//first make porta7 to be 1, after delay, porta7 becomes 0
	BUSREAD(c); c &= 0xf0;	// high nibble first, c becomes 0bxxxx0000
	LCDSTROBE();//first make porta7 to be 1, after delay, porta7 becomes 0
	 BUSREAD(lownibble);	//sent the pinc to lownibble
	return c | lownibble >> 4;
}

char read541(HC541 address, unsigned char t){
	SPICLKL();
	BGATEL(); BUS(BWRITE); BUSWRITE(address); BGATEH();
	delayU(t); SPICLKH(); BGATEL(); PORTC &= 0xf3;
	return SPI(0);
}	//read sensor bit

void write574(HC574 address, char c){
	BGATEL(); BUS(BWRITE); BUSWRITE(address); BGATEH();
	SPI(c);
	BGATEL();
}

void servoSetAddress(char c) {
	u4 = (u4 & 0x1F) | mirror(c & 7);
	write574(U4, u4);
}                      

void backMotorControl(char c){
	u5 = (u5 & 0x78) | (c & 0x87);
	write574(U5, u5);
}

void power(char c) {
	if (c) POWERUP();
	else POWEROFF();
}

void LED(char c) {
	if (c) LEDON();
	else LEDOFF();
}

} //namespace LL


//namespace Sensor
//{
	//char ReadMiddle()
	//{
		//return read541(LL::MIDDLE, 20);
	//}
	//char ReadFront()
	//{
		//return read541(LL::FRONT, 30);
	//}
//}
