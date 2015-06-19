/*//-------------------------------------------------------------------------------
*  PixelgroupEaserInterface.h
*
*  Interface for Pixelgroup Easer
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
#ifndef PIXELGROUP_EASER_INTERFACE_H
#define PIXELGROUP_EASER_INTERFACE_H


//--------------------------------------------------------
// strobing interface
class PixelgroupEaserInterface
{
public:
  
  virtual void update() = 0;
  virtual void update(unsigned long _now) = 0;
};

#endif
