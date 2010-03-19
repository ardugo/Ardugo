#ifndef PMultiplexed7Segments_h
#define PMultiplexed7Segments_h

#include "PTask.h"
#include "PTimer.h"
#include "PShifter595.h"

class P7Segments : public PTask
{
public:
	P7Segments(PShifter595 *shifter, boolean multiplexed = false, int microsPerSegment = 0, boolean active = false);

	// virtual void Setup();
	virtual void OnIdle();

	void SendData(byte data);
	void SendData(byte *data, byte nBytes, int millisChange, boolean repeat);
	void Cls();

protected:
	void AuxSendData(byte data);

protected:
	PShifter595 *m_pShifter;
	boolean m_multiplexed;
	// byte m_millisSegment;
	PTimer m_segmentsTimer;

	byte m_data;
	unsigned long m_currMillisSegment;
	byte m_mask;

	PTimer m_changeTimer;
	byte m_currChar;
	boolean m_repeatSequence;
	byte *m_dataArray;
	byte m_arrayLength;
};

#endif