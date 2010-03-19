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

