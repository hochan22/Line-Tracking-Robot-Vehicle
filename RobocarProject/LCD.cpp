/*
 * LCD.cpp
 *
 * Created: 2016/1/18 23:34:04
 *  Author: Drim
 */ 


#include <avr/pgmspace.h>

#include "Timer.h"
#include "robocar_ll.h"
#include <stdlib.h>
#include <string.h>
#include "LCD.h"
#include "Task.h"

namespace
{

	enum {STATUS=0, RAM=1, BUSY=128};
	enum {POWER_UP_DELAY=7, INTERFACE_SET_DELAY=2, READY=0, NO_LCDM, PRINTING};

	class LCD : Timer, Task {
		public:
		LCD(void) {
			count = state = POWER_UP_DELAY;	//power up delay > 15 ms
			timer::add(*this);		//timer3 has to be already instantiated
			}
		bool print(unsigned char position, const char *s, unsigned char src){
			if (state != READY) return false;
			state = PRINTING;
			source=src;
			flash = s;
			location = ~position;
			character = location > RAM ? position|128 : pgm_read_byte(str++);
			kerAppend(*this);
			return true;
		}
			
		private:	
		unsigned char state, character, location, source;
		const char *str;
		union {const char *flash; char *ram;};
		char readbyte(void){
			return  source == RAM? * ram++: pgm_read_byte(flash++);
		}
		void timeout(void) {
			if (state == POWER_UP_DELAY) {
				count = state = INTERFACE_SET_DELAY;
				LL::lcdWriteByte(0b00110000, STATUS);
				}
			else {
				timer::remove(*this);
				LL::lcdWriteNibble(0b00110000, STATUS);	//Function set -> 8 bit buss
				delayU(120);							//wait for more than 100 us
				LL::lcdWriteNibble(0b00110000, STATUS);	//Function set -> 8 bits bus
				delayU(50);
				LL::lcdWriteNibble(0b00100000, STATUS);	//Function set -> 4 bit bus
				delayU(50);
				LL::lcdWriteByte(0b00101000, STATUS);	//Function set -> 2 lines display
				delayU(50);
				// test for presence of LCDM
				LL::lcdWriteByte(0b01000000, STATUS);	//CGRAM address = 0
				delayU(50);
				LL::lcdWriteByte(0xa5, RAM);			//write a5 to CGRAM[0]
				delayU(50);
				LL::lcdWriteByte(0b01000000, STATUS);	// back to CGRAM[0]
				delayU(50);
				state = LL::lcdReadByte(RAM) == (char)0xa5 ? READY : NO_LCDM;
				print(~STATUS, PSTR("\010\001\006\014"),~RAM);	// clear display and enter mode set
			}
		}
		void task(void){
			if (!character) {state = READY; return;}
			if (!(LL::lcdReadByte(STATUS) & BUSY)) {
				if (location > RAM) {
					LL::lcdWriteByte(character, STATUS);
					location = RAM;
				} else LL::lcdWriteByte(character, location);
				character = readbyte();
			}
			kerAppend(*this);                             
		}
	} lcd;

}

namespace LCD
{

	
	
	static class : public Task {
	public:
		void print(unsigned char position, const char *s, unsigned char src) {
			if(lcd.print(position, s,src)) return;
			print_param.position = position;
			print_param.s = s;
			print_param.src = src;
			kerAppend(*this);
		}
	private:
		struct {
			unsigned char position;
			const char *s;
			unsigned char src;
		} print_param;
		
		void task(void) {
			if(!lcd.print(print_param.position, print_param.s, print_param.src))
				kerAppend(*this);
		}
	} printTask;
	
	void print(unsigned char position, const char *s) {
		printTask.print(position, s, ~RAM);
		//usrCall(printTask);
	}
	void print(unsigned char position, char *s){
		printTask.print(position, (const char *)s, RAM);
	}
		//usrCall(printTask);
		
	void itos(int i, char *b, unsigned char digit) {	// integer to string
		
		bool negative=false;
		if(i<0)	{i=-i; negative=true;}             //if the value<0, print '-'
		b[digit-1] = mod10(&i) + '0';              //print '0' when the result is 0
		for (int k = digit-2; k >= 0; k--) b[k] =i?  mod10(&i) + '0':' ';
		if (negative) 
		for (int m=0;;m++)
		{
			if(b[m]==' ') continue;
			if(m>0) b[m-1]='-';
			break;
		}		
		if (i) b[0] = '*';                     //if the bits is not enough, print '*'
		
	}
	
	void itosbinary(unsigned int i, char *b, unsigned char digit) {	// integer to string
		b[digit-1] = mod2(&i) + '0';
		for (int k = digit-2; k >= 0; k--) b[k] = i ? mod2(&i) + '0' : '0';
		if (i) b[0] = '*';
	}
	
	unsigned int mod10(int *p) {
		int i = *p / 10;
		unsigned int j = *p - i * 10;
		*p = i;
		return j;
	}
	
	unsigned int mod2(unsigned int *p) {
		unsigned int i = *p / 2;
		unsigned int j = *p - i * 2;
		*p = i;
		return j;
	}

}