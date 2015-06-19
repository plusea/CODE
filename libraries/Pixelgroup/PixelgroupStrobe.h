/*//-------------------------------------------------------------------------------
*  PixelgroupStrobe.h
*
*  Header file for PixelgroupStrobe
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
#ifndef PIXELGROUP_STROBE_H
#define PIXELGROUP_STROBE_H


#include "PixelgroupBase.h"
#include "strobe.h"
#include "PixelgroupStrobeInterface.h"


//--------------------------------------------------------
// a pixelgroup with strobing ability
class PixelgroupStrobe :
  public PixelgroupBase,
  public Strobe,
  public PixelgroupStrobeInterface
{
public:
  
  PixelgroupStrobe();
  PixelgroupStrobe(uint8_t count, ...);
  
  // Pixelgroup strobe interface
  void setStrobing(boolean b);
  boolean isStrobing() {return Strobe::isStrobing();};
  
  void update();
  void update(unsigned long _now);
  
  void paint(PixelWriterInterface&);
};

#endif
