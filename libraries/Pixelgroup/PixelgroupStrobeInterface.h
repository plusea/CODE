/*//-------------------------------------------------------------------------------
*  PixelgroupStrobeInterface.h
*
*  Interface for strobing Pixelgroups
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
#ifndef PIXELGROUP_STROBE_INTERFACE_H
#define PIXELGROUP_STROBE_INTERFACE_H


#include "pixelWriterInterface.h"

//--------------------------------------------------------
// strobing interface
class PixelgroupStrobeInterface
{
public:  
  virtual void setStrobing(boolean b) = 0;
  virtual boolean isStrobing() = 0;
  
  virtual void paint(PixelWriterInterface&) = 0;
  
  virtual void update() = 0;
  virtual void update(unsigned long _now) = 0;
};

#endif
