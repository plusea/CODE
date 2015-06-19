/*//-------------------------------------------------------------------------------
*  PixelgroupStrobe.cpp
*
*  Class PixelgroupStrobe. A Pixelgroup with strobing ability
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
#include "PixelgroupStrobe.h"


//--------------------------------------------------------
// constructor, deconstructor
PixelgroupStrobe::PixelgroupStrobe() : PixelgroupBase(), Strobe()
{
}


PixelgroupStrobe::PixelgroupStrobe(uint8_t count, ...) : PixelgroupBase(), Strobe()
{
  va_list args;
  va_start(args, count);

  // setup pixels
  v_setPixels(count, args);
  
  va_end(args);
}



//--------------------------------------------------------
void PixelgroupStrobe::setStrobing(boolean b)
{
  Strobe::setStrobing(b);

  setDirty(true);
}


//--------------------------------------------------------
void PixelgroupStrobe::update()
{
  unsigned long _now = millis();  
  update(_now);
}


void PixelgroupStrobe::update(unsigned long _now)
{
  boolean changed = Strobe::update(_now);
  
  if (changed) setDirty(true);
}


//--------------------------------------------------------
void PixelgroupStrobe::paint(PixelWriterInterface& writer)
{
  // safeties
  if (!isDirty()) return;
  if (getPixels() == 0 || getSize() == 0) return;

	boolean strobeState = !Strobe::isStrobing() || Strobe::getStrobeState();
  
  // mark as clean
  setDirty(false);
  
  
  for (uint8_t i=0; i<getSize(); i++) {
  
    uint8_t pixelIndex = getPixels()[i];
  
    // set pixel color (or black)
    // sets color in pixelWriter
    // sets pixelwriter to dirty
    
		if (!strobeState) {
      writer.setPixelColor(pixelIndex, 0, 0, 0);
    } else {
      writer.setPixelColor((uint8_t)pixelIndex, getR(), getG(), getB());
    }
  }
}





