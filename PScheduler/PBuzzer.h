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

#ifndef PBuzzer_h
#define PBuzzer_h

#include "WProgram.h"
#include "PTask.h"
#include "PTimer.h"

class PBuzzer : public PTask
{
public:
	PBuzzer(byte pin, boolean active = false);
	void PlayTone(int freq, int ms = 0);
	void Quiet();

    virtual void Setup();
	virtual void OnIdle();

protected:
	void PlayLoop();

protected:
	byte m_pin;
	boolean m_nextHigh;
	PTimer m_endTone;
	PTimer m_freq;
};

#endif