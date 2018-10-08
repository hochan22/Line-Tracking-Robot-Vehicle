/*
 * Button.cpp
 *
 * Created: 2016/2/26 1:40:53
 *  Author: Lujiale
 */ 
#include <avr/pgmspace.h>
#include "wheel.h"
#include "LCD.h"
#include "A_Tracing.h"
#include "robocar_ll.h"
#include "PID.h"
#include "A_Counter.h"
#include "ADC.h"
#include "Timer.h"
#include "servo.h"
#include "robocar_ll.h"

#define S1 0b00000001		//The relative position of buttons and switches
#define S2 0b01000000		//..
#define S3 0b00000100		//..
#define S4 0b00000010		//..
#define S5 0b00001000		//..
#define S6 0b00010000		//..
#define S7 0b00100000		//..
#define S8 0b10000000		//The relative position of buttons and switches

#define PERIOD 40

static class Buttons : Timer {
	public:
	Buttons(void)	//initialization
	{
		count = PERIOD;
		P=15;I=80;D=127;   
		VECL=VECR=120;
		content1=dis1;
		content2=dis2;
		state = LL::read541(LL::BUTTONS, 1)|0b00001111;
		MoveState=false;   
		Blinking=0;
		setmode=servomode=0;
		servowidth=10000;
		timer::add(*this);		//timer3 has to be already instantiated
	}// handler functions
	void S1Changed(char);	void S2Changed(char);	void S3Changed(char);	void S4Changed(char);  //buttons
	void S5Changed(char);	void S6Changed(char);	void S7Changed(char);	void S8Changed(char);	//switches
	
	char *getDIS4() {return dis4;}  //To display the value the PID function returned
	
	private:
	bool MoveState,Blinking;
	char state;
	char setmode,servomode;			//setmode: decide which parameter to be changed
	int servowidth;					//control the pulse width of the servo
	char VECL,VECR;					//control the speed
	
	char dis1[17],dis2[17],dis3[17],dis4[17],*content1,*content2;		//display: content1 for line 1, content2 for line 2
	unsigned int P,I,D;				//PID parameters modification
	
	void display();
	void timeout(void){
		
		count = PERIOD;		//restore count
		char b = LL::read541(LL::BUTTONS, 1);    //check the state of switch and button
		char c = b ^ state;                      //check whether the state changes
		
		if(servomode==1)                         //Servo ADC function open
		{	servowidth=(Adc::getChannel(0)+24)*200;
			if(setmode<4)
			Servo::servo_run(servowidth,setmode);
		}
		display();
		
		if (c) {
			state = b;                          //restore the state
			//S1 to S4: do when the button is pressed and released; S5 to S8: o when the switch is changed
			if (S2 & c) S2Changed(S2 & b);		//move or stop
			if (S1 & c) S1Changed(S1 & b);      //set PID and speed
			if (S3 & c) S3Changed(S3 & b);		// variable to be set
			if (S4 & c) S4Changed(S4 & b);		// variable to be set
			if (S5 & c) S5Changed(S5 & b);      //dis1 or dis3
			if (S6 & c) S6Changed(S6 & b);		//dis2 or dis4
			if (S7 & c) S7Changed(S7 & b);		//		
			if (S8 & c) S8Changed(S8 & b);		//
		}
	}
} buttons;
   
void Buttons::S1Changed(char c) 
{
	if (c) 
	{
		if(MoveState == false){
			WHEEL::move(WHEEL::FORWARD);
			//Servo::servo_run(Servo::MIN,2);
			} else {
			WHEEL::move(WHEEL::STOP);
			//Servo::servo_run(Servo::OFF,2);
		}
		MoveState = !MoveState;
	}
}
void Buttons::S2Changed(char c)				//confirm button
{
	if (c)
	{
		if(servomode==0)
		{
			switch(setmode)
			{
				case 1: P=Adc::getChannel(0)>>2; break;
				case 2: I=Adc::getChannel(0); break;
				case 3: D=Adc::getChannel(0)<<1; break;
				case 4: VECL=Adc::getChannel(0)<<1; break;
				case 5: VECR=Adc::getChannel(0)<<1; break;
			}
			pid::trackset(P,I,D);
			track::setspeed(VECL,VECR);
		}		
	}
 }

void Buttons::S3Changed(char c)				//shift right
 {
	if (c)  {setmode++; setmode=setmode==6?0:setmode;} 
	}
	
void Buttons::S4Changed(char c)				//shift left
{
	 if (c) if (c)  {if(setmode==0)setmode=5; else setmode--;} 
}
	
void Buttons::S5Changed(char c)
{
	if (c)                              //if switch off
	{
		content1=dis1;
	}
	else
	content1=dis3;
}
	
void Buttons::S6Changed(char c)
{
	if (c)
	{
		content2=dis2;
	}
	else
		content2=dis4;
}

void Buttons::S7Changed(char c)
{
	
}

void Buttons::S8Changed(char c)
{
	if (c)
	servomode=0;
	else
	servomode=1;
}

void Buttons::display()
{
	if (servomode==0)									//point to the parameter which will be set
	
	{
			switch(setmode)
			{
				case 0:
				{dis1[2]='P'; dis1[7]='I';dis1[12]='D';dis4[10]=' ';dis4[14]=' ';}
				break;
				case 1:
				if (Blinking)
				{dis1[2]='P'; dis1[7]='I';dis1[12]='D';dis4[10]=' ';dis4[14]=' ';}
				else
				{dis1[2]=' ';dis1[7]='I';dis1[12]='D';dis4[10]=' ';dis4[14]=' ';}
				Blinking=!Blinking;
				break;
				case 2:
				if (Blinking)
				{dis1[2]='P'; dis1[7]='I';dis1[12]='D';dis4[10]=' ';dis4[14]=' ';}
				else
				{dis1[2]='P';dis1[7]=' ';dis1[12]='D';dis4[10]=' ';dis4[14]=' ';}
				Blinking=!Blinking;
				break;
				case 3:
				if (Blinking)
				{dis1[2]='P'; dis1[7]='I';dis1[12]='D';dis4[10]=' ';dis4[14]=' ';}
				else
				{dis1[2]='P';dis1[7]='I';dis1[12]=' ';dis4[10]=' ';dis4[14]=' ';}
				Blinking=!Blinking;
				break;
				case 4:
				{dis1[2]='P'; dis1[7]='I';dis1[12]='D';dis4[10]='<';dis4[14]=' ';}
				break;
				case 5:
				{dis1[2]='P'; dis1[7]='I';dis1[12]='D';dis4[10]=' ';dis4[14]='<';}
				break;
			}
		LCD::itos(P,&dis1[0],2);						//set dis1
		dis1[3]=' ';									//
		LCD::itos(I,&dis1[4],3);						//
		dis1[8]=' ';									//
		LCD::itos(D,&dis1[9],3);						//
		if (setmode==1)									//According to different
		LCD::itos(Adc::getChannel(0)>>2,&dis1[13],3);	//parameter
		else if(setmode==2)								//the relative
		LCD::itos(Adc::getChannel(0),&dis1[13],3);		//value of
		else											//ADC will be
		LCD::itos(Adc::getChannel(0)<<1,&dis1[13],3);	//different
														//set dis1
	}
	else
		{												//set dis1 
			LCD::itos((int)(setmode),&dis1[0],2);       //Display the number of servo to be controlled
			LCD::itos((int)(servowidth),&dis1[2],14);   //Display the pulse width
			dis1[8]='N';	dis1[9]=':';				//
		}

	
	LCD::itos((int)track::getposition(),&dis3[0],2);	//set dis3
	dis3[2]=' ';										//
	dis3[3]='E';	dis3[4]=':';						//
	LCD::itos(pid::getLE(),&dis3[5],2);					//
	dis3[7]=' ';										//
	dis3[8]='A';	dis3[9]='E';	dis3[10]=':';		//
	LCD::itos(pid::getAE(),&dis3[11],5);				//set dis3
	
	LCD::print(LCD::LINE1,content1);					//print on line 1
	
	LCD::itosbinary((int)mirror(LL::read541(LL::MIDDLE,30)),&dis2[0],8);		//set dis2
	dis2[8]=' ';	dis2[9]=' ';											//
	LCD::itos(COUNT::getLdis(),&dis2[9],3);									//
	dis2[12]=':';															//
	LCD::itos(COUNT::getRdis(),&dis2[13],3);								//	set dis2	
	
	dis4[6]=' ';										//set dis4
	LCD::itos((int)VECL,&dis4[7],3);					//
	LCD::itos((int)VECR,&dis4[11],3);					//set dis4

	LCD::print(LCD::LINE2,content2);					//print on line 2
}

namespace BUTTON
{
	char* getDIS4() {return buttons.getDIS4();}
	
}