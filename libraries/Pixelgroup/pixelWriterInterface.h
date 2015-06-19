/*//-------------------------------------------------------------------------------
*  PixelWriterInterdface.h
*
*  Interface for PixelWriter
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

#ifndef PIXEL_WRITER_INTERFACE_H
#define PIXEL_WRITER_INTERFACE_H

#include <Arduino.h>

//--------------------------------------------------------
// a pixel writer interface
class PixelWriterInterface
{
public:
  virtual void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b) = 0;
  virtual void setPixelColor(uint16_t n, uint32_t c) = 0;
  
  virtual void show() = 0;
  
  void setDirty(boolean state) {m_dirty = state;};
  boolean isDirty() {return m_dirty;};
  
private:
  boolean     m_dirty;
  
};


#endif
