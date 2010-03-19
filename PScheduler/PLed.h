#ifndef PLed_h
#define PLed_h

#include "WProgram.h"

class PLed
{
public:
	PLed(byte pin);
	virtual void Setup();

	void GoHigh();
	void GoLow();

protected:
	byte m_pin;
};

#endif