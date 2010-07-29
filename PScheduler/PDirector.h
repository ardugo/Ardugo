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
