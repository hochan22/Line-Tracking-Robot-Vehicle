/*
 * ADC.cpp
 *
 * Created: 2/19/2016 3:30:11 PM
 *  Author: Student
 */ 

#include <avr/interrupt.h>
#include "ADC.h"
#include "Timer.h"
#include "Task.h"

namespace {
	class Test : Timer, public Task {
	public:
		Test(void) {
			currentChannel = 0;
			start();
		}
		
		void start(){
			count = 40;
			timer::add(*this);
			//kerAppend(*this);
		}
		int getChannel(char channel){
			return data[channel]>>1;
		}
	private:
		char channels;
		int data[8], currentChannel;
		void timeout(void){
			count = 40;
			
			//kerAppend(*this);
			ADCSRA = (1 << ADEN) // Enable ADC
			| (1 << ADIE) // Enable ADC interrupt
			| (0b001 << ADPS0); // clk/128
			ADMUX = (0b01 << REFS0) // Voltage Reference Selection: AVcc with external capacitor at AREF pin
			| (1 << ADLAR) // left adjusted
			| (0); // Single Ended Input: ADC0
			ADCSRA |= (1 << ADSC); // Start conversion
		};
		void task(void){
			data[0] = ADCH;
		}
	} adcObj;
}


ISR(ADC_vect){
	isrAppend(adcObj);
}


namespace Adc {
	void start(){
		adcObj.start();
	}
	int getChannel(char channel){
		return adcObj.getChannel(channel);
	}
}