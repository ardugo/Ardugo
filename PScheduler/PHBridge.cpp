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

