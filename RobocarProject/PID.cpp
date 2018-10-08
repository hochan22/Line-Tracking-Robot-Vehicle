/*
 * PID.cpp
 *
 * Created: 2016/2/14 12:59:56
 *  Author: lujiale
 */ 
#include "robocar_ll.h"
#include "A_Counter.h"

namespace{
	class PID {
		public:
		PID(unsigned int p, unsigned int i, unsigned int d) {
			P = p; I = i; D = d;ACCMAX=50*i;
		}
		int control(int error);
		void set(unsigned int p, unsigned int i, unsigned int d) 
		{
			P = p; I = i; D = d; ACCMAX=50*i; lastError = accError =0;
		 }
		int getLE(){return lastError;}
		int getAE(){return accError;}

		private:
		unsigned int P, I, D;
		int lastError, accError, ACCMAX;
	} pidSpeed(1, 1, 1),pidTrack(15,80,90),pidSteer(6,1,6);

	int PID::control(int error) {
		int d = error - lastError;
		lastError = error;
		accError += error;
		if (accError > ACCMAX) accError = ACCMAX;
		if (accError < -ACCMAX) accError = -ACCMAX;
		return -(P * error+accError/(int)I+D * d);
	}

	
	
}

namespace pid
{
	int speedcontrol(int error) {return pidSpeed.control(error);}
	int trackcontrol(int error)  {return pidTrack.control(error);}
	int steercontrol(int error)  {return pidSteer.control(error);}
	void trackset(unsigned int p, unsigned int i, unsigned int d) {pidTrack.set(p,i,d);}
	void speedset(unsigned int p, unsigned int i, unsigned int d) {pidSpeed.set(p,i,d);}
	int getLE(){return pidTrack.getLE();}
	int getAE(){return pidTrack.getAE();}
}