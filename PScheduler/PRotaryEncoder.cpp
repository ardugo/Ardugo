#include "PRotaryEncoder.h"
// Interruption
int intTicks = 0;
int intPinB;
void interrupt()
{
	if (digitalRead(intPinB) == HIGH) 
		intTicks--;
	else
		intTicks++;
}

// Class
PRotaryEncoder::PRotaryEncoder(boolean interrupted, byte pinA, byte pinB, unsigned long debouncingMilis, boolean active)
	: m_butA(interrupted ? pinB : pinA, debouncingMilis, !interrupted), m_butB(pinB, debouncingMilis, !interrupted)
{
	m_ticks = 0;
	m_lastClick = 0;
	m_bInterruptedMode = interrupted;
	if (m_bInterruptedMode) {
		attachInterrupt(pinA, interrupt, RISING);
		intPinB = pinB;
	}
}

void PRotaryEncoder::Setup()
{
	m_butA.Setup();
	m_butB.Setup();
}

void PRotaryEncoder::OnIdle()
{
	// Interrupted
	if (m_bInterruptedMode) {
		int ticks = intTicks;
		intTicks = 0;
		if (ticks) {
			m_lastClick = ticks;
			m_ticks += ticks;
		}
		else 
			m_lastClick = 0;
		return;
	}
	
	// Not interrupted
	m_butA.OnIdle();
	m_butB.OnIdle();

	m_lastClick = 0;
	// Check tick
	if (m_butA.GoneHigh()) {
		// CounterClockWise
		if (m_butB.State() == HIGH) {
			m_lastClick = -1;
			m_ticks--;
		}
		// ClockWise
		else {
			m_lastClick = +1;
			m_ticks++;
		}
	}
}

void PRotaryEncoder::Reset()
{
	m_ticks = 0;
}

boolean PRotaryEncoder::Moved()
{
	return m_lastClick;
}

boolean PRotaryEncoder::GoneClkw()
{
	return m_lastClick > 0;
}

boolean PRotaryEncoder::GoneCounterClkw()
{
	return m_lastClick < 0;
}

int PRotaryEncoder::RecentTicks()
{
	return m_lastClick;
}

int PRotaryEncoder::Ticks()
{
	return m_ticks;
}

PButton *PRotaryEncoder::GetButtonA()
{
	return &m_butA;
}

PButton *PRotaryEncoder::GetButtonB()
{
	return &m_butB;
}

