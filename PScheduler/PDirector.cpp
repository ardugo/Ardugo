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

#include "PDirector.h"	

PDirector::PDirector(PTask **buffer, byte nTasks)
{
	m_tasks = buffer;
	m_maxTasks = nTasks;
	m_firstEmpty = 0;
}

boolean PDirector::AddTask(PTask *t)
{
	if (m_firstEmpty >= m_maxTasks)
		return false;
	m_tasks[m_firstEmpty++] = t;
}

void PDirector::Setup(void* (*f)(void))
{
	m_func = f;

	for (int i = 0; i < m_firstEmpty; i++)
		((PTask*)m_tasks[i])->Setup();
}

void PDirector::Loop()
{
	for (int i = 0; i < m_firstEmpty; i++)
		if (((PTask*)m_tasks[i])->IsActive())
			((PTask*)m_tasks[i])->OnIdle();

	m_func = (void* (*)())(*m_func)();
}

