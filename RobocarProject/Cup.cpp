/*
 * Cup.cpp
 *
 * Created: 2016/3/6 0:53:41
 *  Author: lujiale
 */ 
#include "Timer.h"
#include "servo.h"
#include "wheel.h"
#include <avr/interrupt.h>
#include "A_Counter.h"
#include "robocar_ll.h"
#include "A_Tracing.h"
namespace
{	class CUP: Timer
	{	public:
		CUP()
		{	order=0;             //disable the movement
			orderstate=0;
			displaceL=displaceR=0;
			count=1;				//delay
			timer::add(*this);
		}
		void setorderstate(int temp)	{orderstate=temp;}   

		private:
		bool orderstate;
		long order;					//Time counter, to generate different delay
		int displaceL,displaceR;
		void timeout()
		{	count=1;
			switch(order)
			{	case 199:
				WHEEL::speed(70,70);	
				//WHEEL::move(WHEEL::BACKWARD);
				if (mirror(LL::read541(LL::MIDDLE,30))!=0b00111111&&mirror(LL::read541(LL::MIDDLE,30))!=0b01111111)
				{
					//order--;
				}
				break;
				
				case 200:
				COUNT::resetcounter();
				WHEEL::speed(70,70);
				WHEEL::move(WHEEL::ROTATERIGHT);
				break;
				
				case 202:
				displaceL=COUNT::getLdis();
				displaceR=COUNT::getRdis();
				if (displaceL<22)				//rotate for fixed angle
				{	order--;
					if(displaceR>22) order--;
				}
				else
				WHEEL::speed(0,70);
				if (displaceR<22)
				{
					order--;
					if(displaceL>22) order--;
				}
				else
				WHEEL::speed(70,0);
				
				break;
				
				case 204:
				WHEEL::move(WHEEL::STOP);		//stop and move servo
				/*Servo::servo_run(16200,2);
				Servo::servo_run(18200,1);
				Servo::servo_run(13600,0);
				Servo::servo_run(19200,3);*/
				
				Servo::servo_run(13000,2);
				Servo::servo_run(13750,1);
				Servo::servo_run(13150,0);
				Servo::servo_run(13000,3);
				break;
				
				case 250:
				Servo::servo_run(13000,2);
				break;
				case 306:
				Servo::servo_run(13125,2);
				break;
				case 362:
				Servo::servo_run(13250,2);
				break;
				case 475:
				Servo::servo_run(13500,2);
				break;
				case 531:
				Servo::servo_run(13625,2);
				break;
				case 587:
				Servo::servo_run(13750,2);
				break;
				case 643:
				Servo::servo_run(13875,2);
				break;
				case 700:
				Servo::servo_run(14000,2);
				break;
				case 812:
				Servo::servo_run(14250,2);
				break;
				case 925:
				Servo::servo_run(14500,2);
				break;
				case 981:
				Servo::servo_run(14625,2);
				break;
				case 1037:
				Servo::servo_run(14750,2);
				break;
				case 1093:
				Servo::servo_run(14875,2);
				break;
				
				case 1150://300
				Servo::servo_run(22000,3);//close hand
				Servo::servo_run(15000,2);
				break;
				
				case 1200:
				Servo::servo_run(7200,0);//up
				Servo::servo_run(19700,1);
				Servo::servo_run(14550,2);//center
				break;
				//case 350:
				//Servo::servo_run(25200,3);
				//break;
				//case 400:
				//Servo::servo_run(18200,1);
				//break;
				//default:
				//break;
				
				case 1250:
				COUNT::resetcounter();
				WHEEL::speed(70,70);
				WHEEL::move(WHEEL::ROTATELEFT);
				break;
				
				case 1252:
				displaceL=COUNT::getLdis();
				if (displaceL<22)
				{
					order--;
					if(displaceR>22) order--;
				}
				else
				WHEEL::speed(0,80);
				displaceR=COUNT::getRdis();
				if (displaceR<22)
				{
					order--;
					if(displaceL>22) order--;
				}
				else
				WHEEL::speed(80,0);
				break;
				
				case 1254:
				WHEEL::move(WHEEL::STOP);
				break;
				
				case 1300:
				WHEEL::move(WHEEL::FORWARD);
				WHEEL::speed(80,80);
				TIMSK2|=_BV(TOIE2); 
				break;
				
								
			}
			if (orderstate) order++;
		}
	}cup;
}

namespace Cup
{
	void setcuporderstate(int temp) {cup.setorderstate(temp);}
}