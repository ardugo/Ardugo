#ifndef PHBridge_h
#define PHBridge_h

#include "WProgram.h"

class PHBridge
{
public:
	PHBridge(byte pin_enable, byte pin_a, byte pin_b);

	void Stop();
	void Float();
	void Right(byte power);
	void Left(byte power);

protected:
	byte m_penable, m_pa, m_pb;
};

#endif