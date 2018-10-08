/*
 * A_Counter.cpp
 *
 * Created: 2016/2/20 13:27:36
 *  Author: lujiale
 */ 

#define PERIOD 40
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "Timer.h"
#include "Task.h"

namespace
{
	enum _TCCR0A{ZCTC=0b00000010};  //CTC mode
	enum _TCCR1A{OCTC=0b00000000};  //CTC mod
	class Counter: Timer
	{
		public:
		
		Counter()
		{
			count=PERIOD;
			L_CNT=R_CNT=0;
			lnum=rnum=0;
			numberL=numberR=0;
			lastnumberL=lastnumberR=0;  //Initialization
			Ldiff=Rdiff=0;
			
			DDRB&=~(_BV(0));         //Timer0 setting
			PORTB|=_BV(0);
			TCNT0=0;
			TCCR0A=ZCTC;
			TIFR0|=_BV(OCF0A);
			TCCR0B=0b00000111;     //external clock T0, rising edge
			OCR0A=250;
			TIMSK0=0b00000010;     //enable CompA interrupt
			
			DDRB&=~(_BV(1));       //Timer1 setting
			PORTB|=_BV(1);
			TCNT1L=0;
			TIFR1|=_BV(OCF1A);
			TCCR1A=OCTC;
			TCCR1B=0b00001111;     //external clock T1, rising edge
			TCCR1C=0;
			OCR1AL=250;
			TIMSK1=0b00000010;     //enable compa interrupt
			
			timer::add(*this);
		}
		void reset() {L_CNT=R_CNT=lnum=rnum=numberL=numberR=TCNT0=TCNT1L=0;}
		int getleft() {return Ldiff;}       
		int getright() {return Rdiff;}
		int getnumberl() {return numberL;}
		int getnumberr() {return numberR;}
		int lnum,rnum;							  //The higher bits of displacement
		
		private:
		int L_CNT,R_CNT,numberL,numberR;          //numberL&R is the total displacement
		int lastnumberL,lastnumberR,Ldiff,Rdiff;  //L&Rdiff is the speed of the wheels
		
		void timeout()
		{
			count=PERIOD;
			L_CNT=TCNT0;
			R_CNT=TCNT1;
			numberL=lnum*250+L_CNT;
			numberR=rnum*250+R_CNT;
			Ldiff=numberL-lastnumberL;   //use difference to represent speed
			Rdiff=numberR-lastnumberR;   //use difference to represent speed
			lastnumberL=numberL;
			lastnumberR=numberR;			
		}
	}counter;
}

ISR(TIMER0_COMPA_vect)
{
	counter.lnum++;
}

ISR(TIMER1_COMPA_vect)
{
	counter.rnum++;
}


namespace COUNT
{
	void resetcounter() {counter.reset();}
	int getleftspeed() {return counter.getleft();}
	int getrightspeed() {return counter.getright();}
	int getLdis() {return counter.getnumberl();}
	int getRdis() {return counter.getnumberr();}
	
}