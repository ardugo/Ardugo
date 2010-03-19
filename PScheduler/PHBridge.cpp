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

#include "PHBridge.h"

PHBridge::PHBridge(byte pin_enable, byte pin_a, byte pin_b)
{
	m_penable = pin_enable;
	m_pa = pin_a;
	m_pb = pin_b;

	pinMode(m_penable, OUTPUT);
	pinMode(m_pa, OUTPUT);
	pinMode(m_pb, OUTPUT);
	Stop();
}

void PHBridge::Stop()
{
	digitalWrite(m_pa, LOW);
	digitalWrite(m_pb, LOW);
}

void PHBridge::Float()
{
	digitalWrite(m_penable, LOW);
}

void PHBridge::Right(byte power)
{
	digitalWrite(m_pa, LOW);
	digitalWrite(m_pb, HIGH);
	analogWrite(m_penable, power);
}

void PHBridge::Left(byte power)
{
	digitalWrite(m_pa, HIGH);
	digitalWrite(m_pb, LOW);
	analogWrite(m_penable, power);
}

