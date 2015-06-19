/*//-------------------------------------------------------------------------------
*  colorEaser.h
*
*  Header file for ColorEaser
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
#ifndef COLOR_EASER_H
#define COLOR_EASER_H


#include "easer.h"
#include "color.h"

//--------------------------------------------------------
// a color easer
class ColorEaser : public Easer
{
  public:
  ColorEaser();
  ColorEaser(easingFunc);
    
  void setFrom(Color&);
  void setFrom(uint8_t, uint8_t, uint8_t);
  Color& getFrom() {return m_from;};
  
  void setTo(Color&);
  void setTo(uint8_t, uint8_t, uint8_t);
  Color& getTo() {return m_to;};
  
  void setEasing(boolean easing) {m_isEasing = easing;};
  boolean isEasing() {return m_isEasing;};
  
  boolean update(Color& c);
  boolean update(unsigned long _now, Color& c);
  
private:
  Color       m_from;
  Color       m_to;
  
  boolean     m_isEasing;
};


#endif
