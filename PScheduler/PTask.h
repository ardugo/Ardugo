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
