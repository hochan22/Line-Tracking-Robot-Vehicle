/*
 * PID.h
 *
 * Created: 2016/2/21 23:46:34
 *  Author: lujiale
 */ 
#ifndef PID_H_
#define PID_H_


namespace pid
{
	int speedcontrol(int error);
	int trackcontrol(int error); 
	int steercontrol(int error); 
	void trackset(unsigned int p, unsigned int i, unsigned int d);
	void speedset(unsigned int p, unsigned int i, unsigned int d);
	int getLE();
	int getAE();

}


#endif /*COUNTER_H_*/