/*//-------------------------------------------------------------------------------
*  PixelgroupBase.h
*
*  Header file for Pixelgroup Base Class
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
#ifndef PIXELGROUP_BASE_H
#define PIXELGROUP_BASE_H


#include <Arduino.h>

#include "pixelWriter.h"
#include "pixelWriterInterface.h"

#include "color.h"


//--------------------------------------------------------
// pixelgroup base. most simple. just set color
class PixelgroupBase
{
public:
  
  PixelgroupBase();
  PixelgroupBase(uint8_t count, ...);
  ~PixelgroupBase();
  
  
  void setPixels(uint8_t count, ...);
  void addPixel(uint8_t p);
  void removePixel(uint8_t p);
  void clear();
  
  uint8_t* getPixels() {return m_pixels;};
  uint8_t getSize() {return m_pixelLength;};
  uint8_t getPixelIndex(uint8_t);
  
  void setRGB(Color&);
  void setRGB(uint8_t, uint8_t, uint8_t);
  Color& getColor();
  
  uint8_t getR() {return m_color.getR();};
  uint8_t getG() {return m_color.getG();};
  uint8_t getB() {return m_color.getB();};
  
  boolean isDirty() {return m_dirty;};
  void setDirty(boolean state) {m_dirty = state;};
  
  void paint(PixelWriterInterface&);
  
  
protected:
  void v_setPixels(uint8_t count, va_list args);


private:  
  // array of pixel ids
  uint8_t*       m_pixels;
  uint8_t        m_pixelLength;
  
  // pixelgroup colors
  Color           m_color;

  // dirtyflag
  boolean        m_dirty;
  
};

#endif
