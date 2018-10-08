/*
 * RobocarProject.cpp
 *
 * Created: 2016/1/18 23:14:48
 *  Author: Drim
 */ 

#include <stdio.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include "CUP.h"
#include "robocar_ll.h"
#include "wheel.h"
#include "A_Counter.h"
#include "Timer.h"
#include "servo.h"

class Process:Timer
{
	public:
	Process(){lineloca=cupcase=0;count=1;timer::add(*this);}
		
    private:
	char lineloca,cupcase,displaceL,displayceR;
	void timeout()
	{
		count=1;
			switch(cupcase)
			{	case 0:
				lineloca=mirror(LL::read541(LL::MIDDLE,30));
				if (lineloca==0b01111111||lineloca==0b00111111)
				{	TIMSK2&=~_BV(TOIE2);
					WHEEL::move(WHEEL::STOP);
					Cup::setcuporderstate(1);
				cupcase++;}
				break;
				
				case 1:
				lineloca=mirror(LL::read541(LL::FRONT,40));
				if (lineloca==0b11111100||lineloca==0b11111000)
				{	WHEEL::move(WHEEL::STOP);
					COUNT::resetcounter();
					cupcase++;
				}
				break;
				case 19:WHEEL::move(WHEEL::FORWARD); cupcase++; break;
				case 20:
				displaceL=COUNT::getLdis();
				if (displaceL>90)
				{
					
					TIMSK2&=~_BV(TOIE2);
					WHEEL::speed(0,70);
					WHEEL::move(WHEEL::TURNLEFT);
					Servo::servo_run(11400,0);	
					COUNT::resetcounter();
					cupcase++;
				}
				break;
				
				case 21:
				if (COUNT::getRdis()>31)
				{
					COUNT::resetcounter();
					TIMSK2|=_BV(TOIE2);
					WHEEL::speed(70,70);
					WHEEL::move(WHEEL::FORWARD);
					cupcase++;
				}
				break;
				case 22:
				if (COUNT::getLdis()>90&&COUNT::getRdis()>100)
				{
					COUNT::resetcounter();
					WHEEL::move(WHEEL::STOP);
					TIMSK2&=~_BV(TOIE2);
					cupcase++;
				}
				break;
				case 23:
				COUNT::resetcounter();
				WHEEL::speed(70,70);
				WHEEL::move(WHEEL::TURNRIGHT);
				cupcase++;
				break;
				case 24:
				if (COUNT::getLdis()>35)
				{	WHEEL::move(WHEEL::STOP);
					Servo::servo_run(19200,3);	
					cupcase++;
				}
				break;
				default: cupcase++;
				
			}
		
	}		
}process;
int main(void)
{
	
	//char lineloca=0,cupcase=0;
	while (1){
	//{	switch(cupcase)
		//{	case 0:		
			//lineloca=mirror(LL::read541(LL::MIDDLE,30));
			//if (lineloca==0b01111111||lineloca==0b00111111)
			//{	TIMSK2&=~_BV(TOIE2); 
				//WHEEL::move(WHEEL::STOP);	
				//Cup::setcuporderstate(1);
			    //cupcase++;}
			//break;
			
			//case 1:
			//lineloca=mirror(LL::read541(LL::FRONT,40));
			//if (lineloca==0b11101110||lineloca==0b11100111||lineloca==0b11001110)
			//{	WHEEL::speed(0,100);
			//cupcase++;}
			//break;
			//
			//case 2:
			//COUNT::resetcounter();
			//if (COUNT::getLdis()>200&&COUNT::getRdis()>200)
			//WHEEL::move(WHEEL::STOP);
			//cupcase++;
			//break;
	//	}
	}
}