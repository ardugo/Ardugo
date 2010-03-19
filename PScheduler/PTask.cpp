#include "PTask.h"

PTask::PTask(boolean active)
{
  m_active = active;
}
    
void PTask::Activate(boolean active) 
{
  m_active = active;
}

void PTask::OnIdle()
{
}

void PTask::Setup()
{
}

boolean PTask::IsActive()
{
	return m_active;
}