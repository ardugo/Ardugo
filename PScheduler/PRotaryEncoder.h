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

#ifndef PRotaryEncoder_h
#define PRotaryEncoder_h

#include "WProgram.h"
#include "PTask.h"
#include "PButton.h"

class PRotaryEncoder : public PTask
{
public:
	// InterruptedMode: pinA = 0 => pin2; pinA = 1 => pin3 (interruption numbers)
	PRotaryEncoder(boolean interrupted, byte pinA, byte pinB, unsigned long debouncingMilis, boolean active = true);
	
	virtual void Setup();
    virtual void OnIdle();
	void Reset();

	boolean Moved();
	boolean GoneClkw();
	boolean GoneCounterClkw();

	int Ticks();
	int RecentTicks();
	
	PButton *GetButtonA();
	PButton *GetButtonB();

protected:
	PButton m_butA, m_butB;
	int m_ticks;
	int m_lastClick;
	boolean m_bInterruptedMode;
};

#endif