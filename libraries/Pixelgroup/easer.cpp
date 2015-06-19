/*//-------------------------------------------------------------------------------
*  easer.cpp
*
*  Easer Class
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

#include "easer.h"
#include "easerTypes.h"


//--------------------------------------------------------
Easer::Easer() :
  m_easingFunc(EASING_LINEAR)
  ,m_easingType(EASING_IN_OUT)
  ,m_duration(1.0)
  ,m_loop(EASING_LOOP_NONE)
  ,m_startTime(0)
{};



Easer::Easer(easingFunc func) :
  m_easingFunc(func)
  ,m_easingType(EASING_IN_OUT)  
  ,m_duration(1.0)
  ,m_loop(EASING_LOOP_NONE)
  ,m_startTime(0)
{};



//--------------------------------------------------------
void Easer::rewind()
{
  // make it start over the next tick
  m_startTime = 0;
}


boolean Easer::update(double* current)
{
  unsigned long _now = millis();
  
  return update(_now, current);
}


boolean Easer::update(unsigned long _now, double* current)
{
  signed long currentTime = 0;
  
  // did we start already?
  if (m_startTime == 0) {
    // first time... so we start
    m_startTime = _now;    
    return true;
  }
  
  // calc current time
  // take care of type limits
  if (_now >= m_startTime) {
    currentTime = _now - m_startTime;
  } else {
    // type overflow
    currentTime = ULONG_MAX - m_startTime + _now;
  }

  
  // take care about looping, correct currentTime
  switch (m_loop)
  {
    case EASING_LOOP_LOOP:
      
      if (currentTime > m_duration) {
        
        while (currentTime > m_duration) {
          currentTime -= m_duration;
        }
        
        // reset starttime, correct _now with time-overflow
        m_startTime = _now - currentTime;

      }
      break;
      
    case EASING_LOOP_BOUNCE:
      if (currentTime > m_duration) {
        // going reverse correct currentTime
        currentTime = m_duration - (currentTime - m_duration);
        
        if (currentTime < 0) {
          // reverse again...
          currentTime = -currentTime;
          
          // safety in case currentTime > duration
          while (currentTime > m_duration) {
            currentTime -= m_duration;
          }
          
          // reset starttime, correct _now with time-overflow
          m_startTime = _now - currentTime;
        }
      }
      
      break;
      
    case EASING_LOOP_NONE:
    default:
      if (currentTime > m_duration) {
        *current = 1.0;
        
        // early return
        return false;
      }
      break;
  }

  // calculate current [0..1]
  *current = calcCurrent(currentTime);
  
  return true;
}


double Easer::calcCurrent(long currentTime)
{
//    // only linear for now
//  // calc current value
//  switch(m_easingType)
//  {
//    case EASING_IN:
//      *current = (double)currentTime/(double)m_duration;
//      break;
//
//    case EASING_OUT:
//      *current = (double)currentTime/(double)m_duration;
//      break;
//
//    case EASING_IN_OUT:
//      *current = (double)currentTime/(double)m_duration;
//      break;
//
//
//     default:
//       *current = (double)currentTime/(double)m_duration;
//       break;
//   }
  
  
  // only linear for now!
  return (double)currentTime/(double)m_duration;
}
