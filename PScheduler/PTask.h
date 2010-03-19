#ifndef PTask_h
#define PTask_h

#include "WProgram.h"

class PTask
{    
  public:
    PTask(boolean active = true);
	virtual void Setup();
    void Activate(boolean active = true);
    virtual void OnIdle();
	boolean IsActive();

  protected:
    boolean m_active;
};

#endif
