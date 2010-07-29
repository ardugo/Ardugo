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

#include "PButton.h"

PButton::PButton(byte pin, unsigned long debouncingMilis, boolean active) : PTask(active)
{
	m_pin = pin;
	m_debouncingMilis = debouncingMilis;
	Setup();
}

void PButton::Setup()
{
	pinMode(m_pin, INPUT);
	m_lastState = digitalRead(m_pin);
	m_justChanged = true;
	m_currentDebouncing = 0;
}

void PButton::OnIdle()
{
	m_justChanged = false;
	// If I'm debouncing, nothing to do
	if (m_currentDebouncing) {
		if (millis() - m_currentDebouncing < m_debouncingMilis)
			return;
		else 
			m_currentDebouncing = 0;
	}
	
	// Is there a change?
	if (digitalRead(m_pin) != m_lastState) {
		m_justChanged = true;
		m_lastState = (m_lastState == HIGH) ? LOW : HIGH;
		m_currentDebouncing = millis();
	}
}

byte PButton::GetState()
{
	return m_lastState;
}

boolean PButton::GoneHigh()
{
	return (m_lastState == HIGH) && m_justChanged;
}

boolean PButton::GoneLow()
{
	return (m_lastState == LOW) && m_justChanged;
}

int PButton::State()
{
	return m_lastState;
}

int PButton::RawPin()
{
	return digitalRead(m_pin);
}
