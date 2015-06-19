/*//-------------------------------------------------------------------------------
*  strobe.h
*
*  Header file for Strobe
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
#ifndef STROBE_H
#define STROBE_H

#include <Arduino.h>

//--------------------------------------------------------
//
class Strobe
{
public:
  Strobe();
  
      
  void setOnTime(uint16_t time) {m_strobeOnTime = time;};
  void setOnTimeSec(double time) {m_strobeOnTime = (uint16_t)(time*1000.0);};
  uint16_t getOnTime() {return m_strobeOnTime;};
  
  void setOffTime(uint16_t time) {m_strobeOffTime = time;};
  void setOffTimeSec(double time) {m_strobeOffTime = (uint16_t)(time*1000.0);};
  uint16_t getOffTime() {return m_strobeOffTime;};
  
  void setStrobeState(boolean);
  boolean getStrobeState() {return m_state;};  
  
  void setStrobing(boolean);
  boolean isStrobing() {return m_isStrobing;};
  
  
  boolean update();
  boolean update(unsigned long _now);
  
private:
  uint16_t        m_strobeOffTime; // in ms (max 65.535 ms)
  uint16_t        m_strobeOnTime; // in ms (max 65.535 ms)
  
  unsigned long   m_lastUpdate;
  boolean         m_state;
  
  boolean         m_isStrobing;
};


#endif
