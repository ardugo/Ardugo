#ifndef PTimer_h
#define PTimer_h

#include "WProgram.h"
#include "PTask.h"

class PTimer : public PTask
{
public:
	PTimer(boolean inMilis = true);

	void SetTimer(unsigned long ms, boolean repeated = false);
	void RestartTimer();
	void CancelTimer();
    virtual void OnIdle();

	boolean IsFired();

protected:
	void StartTimer(unsigned long ms);

protected:
	boolean m_inMilis;
	unsigned long m_lastStart;
	unsigned long m_milis;
	boolean m_repeated;
	boolean m_fired;
};

#endif