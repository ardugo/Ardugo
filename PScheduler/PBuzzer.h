#ifndef PBuzzer_h
#define PBuzzer_h

#include "WProgram.h"
#include "PTask.h"
#include "PTimer.h"

class PBuzzer : public PTask
{
public:
	PBuzzer(byte pin, boolean active = false);
	void PlayTone(int freq, int ms = 0);
	void Quiet();

    virtual void Setup();
	virtual void OnIdle();

protected:
	void PlayLoop();

protected:
	byte m_pin;
	boolean m_nextHigh;
	PTimer m_endTone;
	PTimer m_freq;
};

#endif