/*//-------------------------------------------------------------------------------
*  strobe.cpp
*
*  strobing class
*  
*  written by: Ingo Randolf - 2014
*
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
//-------------------------------------------------------------------------------*/
#include <limits.h>
#include "strobe.h"


Strobe::Strobe() :
   m_strobeOffTime(250)
  ,m_strobeOnTime(250)
//  ,m_offMultiplier(0.0)
//  ,m_onMultiplier(1.0)
  ,m_lastUpdate(0)
  ,m_state(true)
  ,m_isStrobing(0)
{
}



//--------------------------------------------------------
void Strobe::setStrobing(boolean b)
{
  m_isStrobing = b;
  setStrobeState(false);
}


void Strobe::setStrobeState(boolean state)
{
  m_state = state;
  // reset time
  m_lastUpdate = millis();
}


//--------------------------------------------------------
boolean Strobe::update()
{
  unsigned long _now = millis();
  
  return update(_now);
}


boolean Strobe::update(unsigned long _now)
{
  // if not turned on return false (not changed = not dirty)
  if (!m_isStrobing) return false;
  
  
  // do strobe
  unsigned long diff = 0;
  boolean changed = false;

  // take care of type limits
  if (_now >= m_lastUpdate) {  
    diff = _now - m_lastUpdate;
  } else {
    // type overflow
    diff = ULONG_MAX - m_lastUpdate + _now;
  }
  
  if (m_state) {
    // strobe on
    if (diff > m_strobeOnTime) {
      // turn off
      m_state = false;
      m_lastUpdate = _now;
        
      changed = true;
    }
  } else {
    // strobe off
    if (diff > m_strobeOffTime) {
      // turn on
      m_state = true;
      m_lastUpdate = _now;
      
      changed = true;
    }
  }
  
  // return if state changed or not
  return changed;
}

