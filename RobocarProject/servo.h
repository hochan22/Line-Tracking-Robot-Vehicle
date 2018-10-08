/*
 * servo.h
 *
 * Created: 26/01/2016 04:31:42
 *  Author: Administrator
 */ 


#ifndef SERVO_H_
#define SERVO_H_ 

namespace Servo
{
	enum {OFF=0, MIN=4800, MID=14530, MAX=26648};
		
	void servo_run(unsigned int w,unsigned int chnel);
	
}



#endif /* SERVO_H_ */