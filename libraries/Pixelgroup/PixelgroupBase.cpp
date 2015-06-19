/*//-------------------------------------------------------------------------------
*  PixelgroupBase.cpp
*
*  Pixelgroup Base class. simplest form of pixelgroup can set color
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
#include "PixelgroupBase.h"


//--------------------------------------------------------
// constructor, deconstructor
PixelgroupBase::PixelgroupBase() :
  m_pixels(0)
  ,m_pixelLength(0)
  ,m_dirty(true)
{
}


PixelgroupBase::PixelgroupBase(uint8_t count, ...) :
  m_pixels(0)
  ,m_pixelLength(0)
  ,m_dirty(true)
{
  va_list args;
  va_start(args, count);

  // setup pixels
  v_setPixels(count, args);
  
  va_end(args);
}


PixelgroupBase::~PixelgroupBase()
{
  // cleanup
  if (m_pixels > 0) {
    free(m_pixels);
    m_pixels = 0;
    m_pixelLength = 0;
  }
}


//--------------------------------------------------------
// set pixels - private
void PixelgroupBase::v_setPixels(uint8_t count, va_list args)
{
  // free pixels if any...
  if (m_pixels > 0) {
    free(m_pixels);
    m_pixels = 0;
    m_pixelLength = 0;
  }
  
  
  // create pixels
  // each index is allowed only once
  // re-occurring pixels are getting skipped
  m_pixels = (uint8_t*)malloc(count * sizeof(uint8_t));

  if (m_pixels > 0) { 
  
    // set pixel length 
    m_pixelLength = count;
  
    // fill pixels with data...
    for (uint8_t i=0; i < count; i++) {
  
      // get pixel index
      int p = va_arg(args, int);
    
      if (p >= 0) {
    
        // only allow index once
        if (i > 0) {
        
          uint8_t k;
          for (k=0; k<(i-1); k++) {          
            if (m_pixels[k] == p) break;          
          }
        
          if (k == (i-1)) {
            // all right, pixel not in list
            m_pixels[i] = (uint8_t)p;
          } else {
            // dont add already existing index index
            count--;
            i--;
          }
        
        } else {
          m_pixels[i] = (uint8_t)p;
        }
      } 
    }
  
    if (count != m_pixelLength) {
      // we need to correct!    
      uint8_t* newp = (uint8_t*)malloc(count * sizeof(uint8_t));
    
      if (newp > 0) {
    
        // copy existing pixels
        memcpy(newp, m_pixels, count);
      
        // free old pixels
        free(m_pixels);
      
        // set new pixels
        m_pixels = newp;
    
      }

      // in any case set correct pixelcount
      m_pixelLength = count;
    }
  
  } else {
  // malloc error!!
  }
}



//--------------------------------------------------------
//--------------------------------------------------------
// public functions

// set pixels in this group
void PixelgroupBase::setPixels(uint8_t count, ...)
{
  va_list args;
  va_start(args, count);
  
  v_setPixels(count, args);
  
  va_end(args);
  
  
  // mark as dirty
  m_dirty = true;
}



// add a pixelindex to this group
void PixelgroupBase::addPixel(uint8_t p)
{
  if (m_pixels == 0) {
    
    m_pixels = (uint8_t*)malloc(sizeof(uint8_t));
    
    if (m_pixels > 0) {
    
      // set the only pixel and return
      m_pixels[0] = p;
      m_pixelLength = 1;
    } else {
      //error!
    }
    
    return;
  }
  
  if (m_pixels > 0) {
  
    // check if pixel already exists
    for (uint8_t i=0; i < m_pixelLength; i++) {
        if (m_pixels[i] == p) return;
    }
  
    // pixel is not part of this group, add it
    uint8_t* newp = (uint8_t*)malloc( (m_pixelLength + 1) * sizeof(uint8_t) );
    
    if (newp > 0) {
      // copy old pixels
      memcpy(newp, m_pixels, m_pixelLength);
      
      // set last (new) pixel
      newp[m_pixelLength] = p;
      
      //free old pixels
      free(m_pixels);
      
      // set new pixels
      m_pixels = newp;
            
      // all done, new size
      m_pixelLength++;
    } else {
      // error, could not alloc new pixels
    }
  } else {
    // error!! no pixels?
  }

}

void PixelgroupBase::removePixel(uint8_t p)
{
  // search for pixel
  for (uint8_t i=0; i<m_pixelLength; i++) {
  
    if (m_pixels[i] == p) {
      // found pixel, remove it...
      
      // new pixels
      uint8_t* newp = (uint8_t*)malloc( (m_pixelLength - 1) * sizeof(uint8_t) );
      
      if (newp > 0) {
        
        //copy pixels before i
        if (i>0) {
          memcpy(newp, m_pixels, i);
        }
        
        // copy pixels after i
        if (i < m_pixelLength-1) {
          memcpy(newp+i, m_pixels+i+1, m_pixelLength-i-1);
        }
        
        // all copied
        free(m_pixels);
        
        //
        m_pixels = newp;
        m_pixelLength--;
        
        // each pixel is in list only once
        break;
      }      
    }  
  }
}


void PixelgroupBase::clear()
{
  // free pixels if any...
  if (m_pixels > 0) {
    free(m_pixels);
    m_pixels = 0;
    m_pixelLength = 0;
  }
}



//--------------------------------------------------------
void PixelgroupBase::setRGB(Color& color)
{
  m_color.setRGB(color);
  m_dirty = true;
}

void PixelgroupBase::setRGB(uint8_t _r, uint8_t _g, uint8_t _b)
{
  m_color.setRGB(_r, _g, _b);
  m_dirty = true;
}

Color& PixelgroupBase::getColor()
{
  // return reference
  return m_color;
}


//--------------------------------------------------------
void PixelgroupBase::paint(PixelWriterInterface& writer)
{
  // safeties
  if (!isDirty()) return;
  if (m_pixels == 0 || m_pixelLength == 0) return;
  
  
  // mark as clean
  setDirty(false);
  
  
  for (uint8_t i=0; i<m_pixelLength; i++) {  
    uint8_t pixelIndex = m_pixels[i];    
    writer.setPixelColor((uint8_t)pixelIndex, m_color.getR(), m_color.getG(), m_color.getB());
  }
}





