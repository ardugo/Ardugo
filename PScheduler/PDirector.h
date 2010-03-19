#ifndef PDirector_h
#define PDirector_h

#include "WProgram.h"
#include "PTask.h"


class PDirector
{
public:
	PDirector(PTask **buffer, byte nTasks);

	boolean AddTask(PTask *p);
	
	void Setup(void* (*f)(void));
	void Loop();

protected:
	PTask **m_tasks; // Should be PTask **m_taks;
	byte m_maxTasks;
	byte m_firstEmpty;

	void* (*m_func)(void);
};

#endif
