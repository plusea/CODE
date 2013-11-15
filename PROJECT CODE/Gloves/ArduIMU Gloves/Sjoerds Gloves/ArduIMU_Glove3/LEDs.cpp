/*
    LEDs.cpp
    Author: Seb Madgwick
*/

//------------------------------------------------------------------------------
// Includes

#include <Arduino.h>
#include "LEDs.h"

#include "Wire.h"
#include "BlinkM_funcs.h"

//------------------------------------------------------------------------------
// Definitions

#define RED_LED_PIN     5
#define BLUE_LED_PIN    6
#define YELLOW_LED_PIN  13  // LED unavailable as pin used by MPU-6000

//------------------------------------------------------------------------------
// Methods

void LEDs::init() {
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);
  BlinkM_begin();
  BlinkM_fadeToRGB(9,0,0,0);
}

void LEDs::setled(int foo, int bar, int bap) {

  BlinkM_fadeToRGB(9,foo,bar,bap);
}


void LEDs::setRed(bool state) {
    digitalWrite(RED_LED_PIN, state ? HIGH: LOW);
}

void LEDs::setBlue(bool state) {
    digitalWrite(BLUE_LED_PIN, state ? HIGH: LOW);
}

//------------------------------------------------------------------------------
// End of file
