/*
 * Timer.cpp
 *
 * Created: 2016/1/18 23:20:11
 *  Author: Drim
 */ 


#include <avr/interrupt.h>
#include "Task.h"
#include "Timer.h"
#include "robocar_ll.h"
#include "wheel.h"
static class Timer3 : public Task {
	public:
	
	Timer3(void) : current(0) {
		TCCR3A = 0b00000011;	// OC3A & OC3B disconnected, Fast PWM
		TCCR3B = 0b00011001;	// clk/1
		OCR3A = 46080;			// 2.5 ms for 18.432 MHz
		TIMSK3 |= _BV(TOIE3);	// enable interrupt
	}
	void add(Timer &t) {list.append(t);}
	void remove(Timer &t) {
		Timer* e = (Timer*)list.remove(t);
		if (e) if (current == &t) current = e;
	}
	private:
	List list;
	Timer *current;
	void task(void) 
	{
		if ((current = (Timer*)list.getNext(current))) 
		{
			if (--current->count == 0) current->timeout();
			kerAppend(*this);			
		}
	}
	
	void linetracing();
} timer3;

ISR(TIMER3_OVF_vect) {
	isrAppend(timer3);}

namespace timer
{
	void add(Timer &t) {timer3.add(t);}
	void remove(Timer &t) {timer3.remove(t);}
}

