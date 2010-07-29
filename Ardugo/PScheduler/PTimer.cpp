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

#include "PTimer.h"

PTimer::PTimer(boolean inMilis) : PTask(false)
{
	m_inMilis = inMilis;
}

void PTimer::StartTimer(unsigned long ms)
{
	m_lastStart = m_inMilis ? millis() : micros();
	m_milis = ms;
	Activate();
}

void PTimer::SetTimer(unsigned long ms, boolean repeated)
{
	m_fired = false;
	StartTimer(ms);
	m_repeated = repeated;
}

void PTimer::CancelTimer()
{
	m_fired = false;
	Activate(false);
}

void PTimer::RestartTimer()
{
	StartTimer(m_milis);
}

void PTimer::OnIdle()
{
	unsigned long current = m_inMilis ? millis() : micros();
	if (current - m_lastStart >= m_milis) {
		m_fired = true;
		if (m_repeated)
			m_lastStart = m_lastStart + m_milis * ((current - m_lastStart) / m_milis);
		else
			Activate(false);
	}
	else
		m_fired = false;
}

boolean PTimer::IsFired()
{
	return m_fired;
}
