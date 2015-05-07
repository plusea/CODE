/*
    VinbrationMotor.cpp
    Author: Seb Madgwick
*/

//------------------------------------------------------------------------------
// Includes

#include <Arduino.h>
#include "VibrationMotor.h"

#define VIBRATION_MOTOR_PIN     10

//------------------------------------------------------------------------------
// Definitions

//------------------------------------------------------------------------------
// Variables

//------------------------------------------------------------------------------
// Methods

void VibrationMotor::init() {
    
  pinMode(VIBRATION_MOTOR_PIN,OUTPUT);
  analogWrite(VIBRATION_MOTOR_PIN,0);
    
}

void VibrationMotor::doTasks() {
}

void VibrationMotor::pulse(const char num) {
    
  analogWrite(VIBRATION_MOTOR_PIN,num);
    
}

//------------------------------------------------------------------------------
// End of file
