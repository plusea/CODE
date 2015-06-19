/*//-------------------------------------------------------------------------------
*  easerTypes.h
*
*  EaserTypes
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
#ifndef EASER_TYPES_H
#define EASER_TYPES_H


typedef enum easingFunc_t {
  EASING_BACK = 0,
  EASING_BOUNCE,
  EASING_CIRCULAR,
  EASING_CUBIC,
  EASING_ELASTIC,
  EASING_EXPONENTIAL,
  EASING_LINEAR,
  EASING_QUADRATIC,
  EASING_QUARTIC,
  EASING_QUINTIC,
  EASING_SINE,
  
  EASING_MAX
} easingFunc;


typedef enum easingType_t {
  EASING_IN = 0,
  EASING_OUT,
  EASING_IN_OUT,
  
  EASING_TYPE_MAX
} easingType;


typedef enum easingLoop_t {
  EASING_LOOP_NONE = 0,
  EASING_LOOP_LOOP,
  EASING_LOOP_BOUNCE,
  
  EASING_LOOP_MAX
} easingLoop;


#endif
