/*//-------------------------------------------------------------------------------
*  color.h
*
*  Header file for color
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

#ifndef COLOR_H
#define COLOR_H

#include <Arduino.h>

//--------------------------------------------------------
// color
class Color
{  
public:
  Color();
  Color(uint8_t, uint8_t, uint8_t);  
  Color(const Color&);
  
  void operator*=(double f);
  Color& operator*(double f);
  
  void setRGB(uint8_t, uint8_t, uint8_t);
  void setRGB(Color&);
  void setR(uint8_t);
  void setG(uint8_t);
  void setB(uint8_t);
  uint8_t getR() {return r;};
  uint8_t getG() {return g;};
  uint8_t getB() {return b;};
  
  
private:
  uint8_t  r;
  uint8_t  g;
  uint8_t  b;
};


#endif
