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

#include "P7Segments.h"

P7Segments::P7Segments(PShifter595 *shifter, boolean multiplexed, int microsPerSegment, boolean active) 
	: PTask(active), m_segmentsTimer(false)
{
	m_pShifter = shifter;
	m_multiplexed = multiplexed;
	m_segmentsTimer.Setup();
	if (m_multiplexed) {
		// Preprogram the timer
		m_segmentsTimer.SetTimer(microsPerSegment, true);
		m_segmentsTimer.CancelTimer();
	}
}

void P7Segments::OnIdle()
{
	if (m_segmentsTimer.IsActive())
		m_segmentsTimer.OnIdle();
	if (m_changeTimer.IsActive())
		m_changeTimer.OnIdle();

	// Do I have to change the character?
	if (m_changeTimer.IsFired()) {
		// Do I have to finish?
		m_currChar++;
		if (!m_repeatSequence && m_currChar == m_arrayLength) {
			Cls();
			return;
		}
		
		if (m_currChar == m_arrayLength) m_currChar = 0;

		AuxSendData(m_dataArray[m_currChar]);
	}
	
	// Check segment change
	if (m_segmentsTimer.IsFired()) {
		if (m_mask == B0000001)
			m_mask = B10000000;
		else
			m_mask >>= 1;

		m_pShifter->SendData(m_data & m_mask);
	}
}

void P7Segments::SendData(byte data)
{
	m_changeTimer.Activate(false);
	AuxSendData(data);
}

void P7Segments::AuxSendData(byte data)
{
	if (m_multiplexed) {
		m_segmentsTimer.RestartTimer();
		m_data = data;
		m_mask = B00000001;
		Activate();
	}
	else
		m_pShifter->SendData(data);
}

void P7Segments::SendData(byte *data, byte nBytes, int millisChange, boolean repeat)
{
	m_changeTimer.SetTimer(millisChange, true);
	m_dataArray = data;
	m_arrayLength = nBytes;
	m_currChar = 0;
	m_repeatSequence = repeat;
	
	// Prepare the first char
	AuxSendData(data[0]);

	Activate();
}

void P7Segments::Cls()
{
	Activate(false);
	m_segmentsTimer.CancelTimer();
	m_changeTimer.CancelTimer();
	m_pShifter->SendData((byte)0);
}
