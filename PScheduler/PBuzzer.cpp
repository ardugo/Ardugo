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

#include "PBuzzer.h"

PBuzzer::PBuzzer(byte pin, boolean active) : PTask(active), m_freq(false)
{
	m_pin = pin;
	Setup();
}

void PBuzzer::Setup()
{
	pinMode(m_pin, OUTPUT);
	digitalWrite(m_pin, LOW);
}

void PBuzzer::PlayTone(int freq, int ms)
{
	if (ms) 
		m_endTone.SetTimer(ms);
	else
		m_endTone.CancelTimer();
		
	m_freq.SetTimer(freq, true);

	if (IsActive() && !m_nextHigh)
		digitalWrite(m_pin, LOW);

	Activate();
	m_nextHigh = true;
	PlayLoop();
}

void PBuzzer::OnIdle()
{
	if (m_endTone.IsActive()) 
		m_endTone.OnIdle();
	m_freq.OnIdle();
	
	if (m_endTone.IsFired()) {
		digitalWrite(m_pin, LOW);
		Activate(false);
	}
	else
		if (m_freq.IsFired())
			PlayLoop();
}

void PBuzzer::PlayLoop()
{
	digitalWrite(m_pin, m_nextHigh ? HIGH : LOW);
	m_nextHigh = !m_nextHigh;
}

void PBuzzer::Quiet()
{
	digitalWrite(m_pin, LOW);
	Activate(false);
}