/*//-------------------------------------------------------------------------------
*  easer.h
*
*  Header file for Easer
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
#ifndef EASER_H
#define EASER_H


#include <Arduino.h>

#include "easerTypes.h"


//--------------------------------------------------------
// easer (linear only for now)
class Easer
{
public:
  Easer();
  Easer(easingFunc);
  
  void setEasingFunc(easingFunc func) {m_easingFunc = func;};
  uint8_t getEasingFunc() {return m_easingFunc;};
  
  void setEasingType(easingType _type) {m_easingType = _type;};
  uint8_t getEasingType() {return m_easingType;};
  
  void setDuration(uint16_t dur) {m_duration = dur;};
  uint16_t getDuration() {return m_duration;};
  
  void setLoop(easingLoop _loop) {m_loop = _loop;};
  uint8_t getLoop() {return m_loop;};
  
  void rewind();
  
  boolean update(double*);
  boolean update(unsigned long, double*);
  
private:
  
  double calcCurrent(long);
  
  uint8_t      m_easingFunc;
  uint8_t      m_easingType;
  uint16_t     m_duration; // in milliseconds (max 65536 ms)
  
  uint8_t      m_loop;
  
  unsigned long  m_startTime;
};


#endif
