/*
 * wheel.h
 *
 * Created: 26/01/2016 05:42:06
 *  Author: Administrator
 */ 


#ifndef WHEEL_H_
#define WHEEL_H_


namespace WHEEL
{
	enum _command{STOP=0,
		FORWARD=0b10100111,
		BACKWARD=0b10100100,
		ROTATELEFT=0b10101010,
		ROTATERIGHT=0b10101001,
		TURNLEFT=0b00101111,
		TURNRIGHT=0b10001111,
		BTURNLEFT=0b10001100,
		BTURNRIGHT=0b00101100
		};
	void move(enum _command);
	void speed(char left_speed,char right_speed);
}


#endif /* WHEEL_H_ */