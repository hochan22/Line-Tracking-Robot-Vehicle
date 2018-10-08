/*
 * timer.h
 *
 * Created: 2016/1/18 23:27:33
 *  Author: Drim
 */ 


#ifndef __TIMER_H__
#define __TIMER_H__

#include "List.h"

class Timer : Element {
	
	protected:
	unsigned int count;
	private:
	virtual void timeout(void)=0;
	friend class Timer3;
};

namespace timer
{
	void add(Timer &t);
	void remove(Timer &t);
}

#endif //__TIMER_H__