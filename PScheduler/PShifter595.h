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