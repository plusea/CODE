/*//-------------------------------------------------------------------------------
*  pixelwriter.h
*
*  Header file for PixelWriter
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

#ifndef PIXEL_WRITER_H
#define PIXEL_WRITER_H

#include "pixelWriterInterface.h"

// 'type' flags for LED pixels (third parameter to constructor):
#define PXW_RGB     0x00 // Wired for RGB data order
#define PXW_GRB     0x01 // Wired for GRB data order
#define PXW_BRG     0x04

class Color;

//--------------------------------------------------------
// pixel writer
// holds pointer to pixel array
class PixelWriter : public PixelWriterInterface
{
public:  
  PixelWriter(uint8_t* _pixels, uint8_t _count, uint8_t order=PXW_GRB);
  
  virtual void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
  virtual void setPixelColor(uint16_t n, uint32_t c);
   
  void setShowFunc( void (*)(void) );
  boolean isShowFunc() {return (showFunc>0);};
  void show();

private:
  uint8_t*  m_pixels;
  uint8_t  m_pixelCount;
   
  uint8_t rOffset;       // Index of red byte within each 3-byte pixel
  uint8_t gOffset;       // Index of green byte
  uint8_t bOffset;       // Index of blue byte
   
  // callbacks
  void (*showFunc)(void);  
};


#endif
