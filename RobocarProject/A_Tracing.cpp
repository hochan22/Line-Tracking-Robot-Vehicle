
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "Timer.h"
#include "robocar_ll.h"
#include "wheel.h"
#include "Task.h"
#include "PID.h"
#include "A_Counter.h"
#include "LCD.h"
#include "Button.h"
#include "trackTable.h"
#define delay_t 1


namespace
{
class Tracing : public Task{
	public:
	Tracing(void) {
		 VECL=120;
		 VECR=120;	
		TIMSK2|=_BV(TOIE2);     //enable overflow interrupt
		position=8;
		leftspeed=VECL;
		rightspeed=VECR;
	}
	
	char getposition() {return position;}
	void setspeed(char a,char b){VECL=a;VECR=b;}
	
	private:
	char leftspeed,rightspeed,VECL,VECR;
	char position;

	void linetracing();
	void task(void){
		linetracing();
	}
} tracing;

ISR(TIMER2_OVF_vect)
{
	isrAppend(tracing);
}

void Tracing::linetracing()
{	
	
	int d;	
	position=POSITION::displacement(mirror(LL::read541(LL::FRONT,40)));
	d=pid::trackcontrol(position-8);			//PID return
	LCD::itos(d,BUTTON::getDIS4(),6);           //display the value that the PID function returned
	
	leftspeed=VECL+d>250?250:VECL+d;
	leftspeed=VECL+d<0?0:VECL+d;
	
	rightspeed=VECR-d>250?250:VECR-d;
	rightspeed=VECR-d<0?0:VECR-d;
	WHEEL::speed(leftspeed,rightspeed);			//speed adjust
}
	}
	
namespace track
{
	void setspeed(char VECL,char VECRT) {tracing.setspeed(VECL,VECRT);}
	char getposition() {return tracing.getposition();}
}

