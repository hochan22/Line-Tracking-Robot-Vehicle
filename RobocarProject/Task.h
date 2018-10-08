/* 
* Task.h
*
* Created: 2/10/2015 9:55:53 PM
* Author: Student
*/


/*
*  There are 3 running levels:	ISR level
*                               kernel level
*                               user level
*  user level - starts from main().
*             - switches to ISR level by interrupts.
*             - the only place for running LONG computation.
*             - allows for procedural programming.
*  kernel level - entered via isrAppend(Task&) from ISR level.
*               - switches to ISR level by interrupts.
*               - return to user level when nothing left in the Task queues.
*               - write SHORT event/interrupt handlers to run at kernel level.
*               - better use OOP here.
*  ISR level - those interrupt service routines.
*            - whenever possible, leaves job to kernel level.
*/


#ifndef __TASK_H__
#define __TASK_H__

#include "List.h"

class Task : Element {
private:
	virtual void task(void)=0;
friend void isrAppend(Task&);
};

class Queue {
public:
	Queue(Queue*);
	void append(Task&);
private:
	void push(Task&);
	Task* pop(void);
	List queue;
	Queue* next;
	bool popping;
friend void isrAppend(Task&);
};

void isrAppend(Task&);	//call it at the end of ISR
void kerAppend(Task&);	//call it at kernel level
void usrCall(Task&);	//call kernel at user level

#endif //__TASK_H__
