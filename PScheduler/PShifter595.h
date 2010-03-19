#ifndef PShifter595_h
#define PShifter595_h

#include "WProgram.h"

class PShifter595
{
public:
	static byte digits09[10]; 

public:
	PShifter595(byte clock /* from pin 11 */,
				byte latch /* from pin 12 */,
				byte data /* from pin 14 */);

	void Setup();
	void SendData(byte data);

protected:
	byte m_clock, m_latch, m_data;
};

#endif