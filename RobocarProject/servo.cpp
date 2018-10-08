/*
 * servo.cpp
 *
 * Created: 26/01/2016 04:31:55
 *  Author: Jack Lee
 */ 
#include <avr/interrupt.h>
#include "servo.h"
#include "Task.h"
#include "robocar_ll.h"

namespace//other files cannot access the content in this namespace
{
	unsigned int width[8];//store the pulse width of each channel (totally 8)
	//going to be send to OCR3B to set the time of compare match B
	unsigned char channel;//channel number
	
	unsigned int set(unsigned int w) {
		if (w > Servo::MAX) return Servo::MAX;
		if (w > Servo::MIN) return w;
		if (w) return Servo::MIN;
	else return 0;}
	

	
class SERVO : public Task {
	public:
	SERVO(void){
		DDRB |= _BV(7);			//OC3B as output
		OCR3B = Servo::MID;
		TIMSK3 |= _BV(OCIE3B);
		channel = width[0] = width[1] = Servo::OFF;	//
		width[2] = width[5] = Servo::OFF;		//
		width[4] = width[3] = Servo::OFF;		//
		width[6] = width[7] = Servo::OFF;	//
	}
	
		void servoseting(unsigned int w, unsigned int chnel)
		{	
			chnel&=7;
			width[chnel]=set(w);
		}
	private:
	
	void task(void){
		channel++;
		LL::servoSetAddress(channel &= 7);
		if (width[channel]) {
			OCR3B = width[channel];
			TCCR3A |= _BV(COM3B1);		//connect o/p pin
			} else {						//turn off servo by
			OCR3B = Servo::MID;
			TCCR3A &= ~_BV(COM3B1);		//disconnect o/p pin
		}
	}
}servo;

}

ISR(TIMER3_COMPB_vect) {isrAppend(servo);}		//assume timer3 is set fast pwm, period 2.5ms




namespace Servo
{
	void servo_run(unsigned int w, unsigned int chnel) 
	{
		servo.servoseting(w,chnel);
	}
}


