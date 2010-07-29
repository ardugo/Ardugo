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

#ifndef PTimer_h
#define PTimer_h

#include "WProgram.h"
#include "PTask.h"

class PTimer : public PTask
{
public:
	PTimer(boolean inMilis = true);

	void SetTimer(unsigned long ms, boolean repeated = false);
	void RestartTimer();
	void CancelTimer();
    virtual void OnIdle();

	boolean IsFired();

protected:
	void StartTimer(unsigned long ms);

protected:
	boolean m_inMilis;
	unsigned long m_lastStart;
	unsigned long m_milis;
	boolean m_repeated;
	boolean m_fired;
};

#endif