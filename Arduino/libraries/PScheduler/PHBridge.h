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