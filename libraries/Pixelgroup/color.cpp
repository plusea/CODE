/*//-------------------------------------------------------------------------------
*  color.cpp
*
*  Color class
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

#include "color.h"

//--------------------------------------------------------
// color
Color::Color() :
  r(0)
  ,g(0)
  ,b(0)
{
}

Color::Color(uint8_t _r, uint8_t _g, uint8_t _b) :
  r(_r)
  ,g(_g)
  ,b(_b)
{
}

Color::Color(const Color& c) :
  r(c.r)
  ,g(c.g)
  ,b(c.b)
{  
}



void Color::setRGB(uint8_t _r, uint8_t _g, uint8_t _b)
{
  r = _r;
  g = _g;
  b = _b;
}


void Color::setRGB(Color& color)
{
  r = color.getR();
  g = color.getG();
  b = color.getB();
}



void Color::setR(uint8_t _r)
{
  r = _r;
}

void Color::setG(uint8_t _g)
{
  g = _g;
}

void Color::setB(uint8_t _b)
{
  b = _b;
}


void Color::operator*=(double f)
{
  if (f <= 0) {
    r = g = b = 0;
    return;
  }
  
  if (f == 1.0) return;
  
  r *= f;
  g *= f;
  b *= f;
}

Color& Color::operator*(double f)
{
  if (f <= 0) {
    r = g = b = 0;
    return *this;
  }
  
  if (f == 1.0) return *this;
  
  r *= f;
  g *= f;
  b *= f;
  
  return *this;
}