/*
 * wheel.cpp
 *
 * Created: 26/01/2016 05:42:26
 *  Author: Administrator
 */ 
#include <avr/interrupt.h>
#include "wheel.h"
#include "Task.h"
#include "robocar_ll.h"

#define R_OCR OCR2B
#define L_OCR OCR2A

namespace
{
	enum _motor{B_DIR=1,A_DIR=2,FREE=4,ON=128};
	enum _TCCR2A{A_CON=0b10000011,B_CON=0b00100011,DISCON=0b00000011};
		
	class Timer2{
		public:
		Timer2(void){
			DDRD|=_BV(7);
			DDRD|=_BV(6);
			TCCR2A=DISCON;
			TCCR2B=0b00000111;     //clk prescale
			ASSR&=~_BV(AS2);
			move(WHEEL::STOP);
			L_OCR=R_OCR=120;
		}
		void move(unsigned char command){
			if(command==WHEEL::STOP){		
				TCCR2A=DISCON;
				LL::backMotorControl(ON);
			}else{
				LL::backMotorControl((command&0b11)|FREE|ON);
				TCCR2A=(command&0b11110000)|0b11;
			}
		}
		
		void setspeed(char left_speed,char right_speed)
		{
			L_OCR=left_speed;
			R_OCR=right_speed;
		}
		}timer2;
}

namespace WHEEL{
	void move(enum _command c)
	{timer2.move((unsigned char)c);}
	void speed(char left_speed,char right_speed)
	{
		timer2.setspeed(left_speed,right_speed);
	}
	
}

