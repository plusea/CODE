/*//-------------------------------------------------------------------------------
*  colorEaser.cpp
*
*  Color Easer class based on Easer
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

#include "colorEaser.h"
#include "color.h"


//--------------------------------------------------------
// constructor
ColorEaser::ColorEaser() : Easer()
  ,m_isEasing(false)
{};

ColorEaser::ColorEaser(easingFunc func) : Easer(func)
  ,m_isEasing(false)
{};



//--------------------------------------------------------
void ColorEaser::setFrom(Color& _c)
{
  m_from.setRGB(_c);
}

void ColorEaser::setFrom(uint8_t r, uint8_t g, uint8_t b)
{
  m_from.setRGB(r, g, b);
}

void ColorEaser::setTo(Color& _c)
{
  m_to.setRGB(_c);
}

void ColorEaser::setTo(uint8_t r, uint8_t g, uint8_t b)
{
  m_to.setRGB(r, g, b);
}


//--------------------------------------------------------
boolean ColorEaser::update(Color& c)
{
  unsigned long _now = millis();
  
  return update(_now, c);
}


// return dirty flag
boolean ColorEaser::update(unsigned long _now, Color& c)
{
  // we are not easing
  // we are clean
  // return
  if (!m_isEasing) return false;
  
  
  // do easing
  double percent;  
  m_isEasing = Easer::update(_now, &percent);
   
  double rd = m_to.getR() - m_from.getR();
  double gd = m_to.getG() - m_from.getG();
  double bd = m_to.getB() - m_from.getB();
  
  uint8_t r = (uint8_t)(m_from.getR() + (percent * rd));
  uint8_t g = (uint8_t)(m_from.getG() + (percent * gd));
  uint8_t b = (uint8_t)(m_from.getB() + (percent * bd));
	
  // set color
  c.setRGB(r, g, b);
  
  // we are dirty
  return true;
}
