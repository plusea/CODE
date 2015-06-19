/*//-------------------------------------------------------------------------------
*  Pixelwriter.cpp
*
*  Pixelwriter which satisfies PixelWriterInterface
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

#include "pixelWriter.h"
#include "color.h"

PixelWriter::PixelWriter(uint8_t* pixels, uint8_t pixelCount, uint8_t order) :
  m_pixels(pixels)
  ,m_pixelCount(pixelCount)
  ,showFunc(0)
  ,rOffset(1)
  ,gOffset(0)
  ,bOffset(2)
{
  setDirty(true);
  
  if(order & PXW_RGB) {
    rOffset = 0;
    gOffset = 1;
    bOffset = 2;
  } else if (order & PXW_BRG) {
    rOffset = 1;
    gOffset = 2;
    bOffset = 0;
  }
}



void PixelWriter::setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b)
{
  if(n < m_pixelCount) {
    uint8_t *p = &m_pixels[n * 3];

    // set pixels
    p[rOffset] = r;
    p[gOffset] = g;
    p[bOffset] = b;

    setDirty(true);
  }

}


void PixelWriter::setPixelColor(uint16_t n, uint32_t c)
{
  if(n < m_pixelCount) {
    uint8_t *p = &m_pixels[n * 3];
    
    // set pixels
    p[rOffset] = (uint8_t)(c >> 16); // Red
    p[gOffset] = (uint8_t)(c >>  8); // Green
    p[bOffset] = (uint8_t)c;     // Blue
    
    setDirty(true);
  }
  
}



void PixelWriter::setShowFunc( void (*function)(void) )
{
  showFunc = function;
}


void PixelWriter::show()
{
  if (isDirty() && showFunc != 0) {
    showFunc();
    setDirty(false);
  }
}