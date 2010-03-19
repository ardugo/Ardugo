#include "PShifter595.h"


byte PShifter595::digits09[10] = {B00111111, B00000110, B01011011, B01001111, B01100110, B01101101, B01111100, B00000111, B01111111, B01100111};

PShifter595::PShifter595(byte clock, byte latch, byte data)
{
	m_clock = clock;
	m_latch = latch;
	m_data = data;
	Setup();
}

void PShifter595::Setup()
{
	pinMode(m_latch, OUTPUT);
	digitalWrite(m_latch, HIGH);
	pinMode(m_clock, OUTPUT);
	digitalWrite(m_clock, LOW);
	pinMode(m_data, OUTPUT);
}

void PShifter595::SendData(byte data)
{
    digitalWrite(m_latch, LOW);
    shiftOut(m_data, m_clock, MSBFIRST, data);
    digitalWrite(m_latch, HIGH);
}
