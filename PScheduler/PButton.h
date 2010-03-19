#ifndef PButton_h
#define PButton_h

#include "WProgram.h"
#include "PTask.h"

class PButton : public PTask
{
public:
	PButton(byte pin, unsigned long debouncingMilis, boolean active = true);
	virtual void Setup();
    virtual void OnIdle();

	byte GetState();
	boolean GoneHigh();
	boolean GoneLow();

	int State();
	int RawPin();

protected:
	byte m_pin;
	byte m_lastState;
	boolean m_justChanged;
	unsigned long m_currentDebouncing;
	unsigned long m_debouncingMilis;
};

#endif