///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// This file is part of the PScheduler library by Ardugo
// More info at http://ardugonic.blogspot.com
// You can download the full library and other code from my public
// github repository at http://github.com/ardugo/Ardugo
// Licensed under Creative Commons Attribution Non-Commercial Share Alike (cc by-nc-sa)
// (additional info at http://creativecommons.org/licenses/by-nc-sa/3.0/)
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

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