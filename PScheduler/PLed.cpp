#include "PLed.h"

PLed::PLed(byte pin)
{
	m_pin = pin;
	Setup();
}

void PLed::Setup()
{
	pinMode(m_pin, OUTPUT);
	GoLow();
}

void PLed::GoHigh()
{
	digitalWrite(m_pin, HIGH);
}

void PLed::GoLow()
{
	digitalWrite(m_pin, LOW);
}
