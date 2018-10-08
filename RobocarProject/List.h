/* 
* List.h
*
* Created: 2/10/2015 9:10:04 PM
* Author: Student
*/

/*
	leader -> element -> .... -> element -> leader
	last ------------------------^

	empty list:	leader -> leader
				last   -> leader
*/

#ifndef __LIST_H__
#define __LIST_H__

class Element {		//base class of Task and Listener
public:
	Element(void);
	bool idle(void);
private:
	Element* next;
friend class List;
};

class List {
public:
	List(void);
	bool empty(void);
	Element* getNext(Element*);		//input 0 to get first
	void push(Element&);            //Add elements after the leader.
	void append(Element&);
	Element* pop(void);
	Element* remove(Element& e);	//return element previous to e
private:
	Element leader, *last;
};


#endif //__LIST_H__
