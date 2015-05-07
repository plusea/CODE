/*
    FlexSensors.cpp
    Author: Seb Madgwick
*/

//------------------------------------------------------------------------------
// Includes

#include <Arduino.h>
#include "FlexSensors.h"

//------------------------------------------------------------------------------
// Variables

int FlexSensors::channel[6];

//------------------------------------------------------------------------------
// Methods

void FlexSensors::init() {
    digitalWrite(A0, HIGH); // enable pull-ups
    digitalWrite(A1, HIGH);
    digitalWrite(A2, HIGH);
    digitalWrite(A3, HIGH);
    // digitalWrite(A6, HIGH); // no pull-ups on these pins
    // digitalWrite(A7, HIGH);
}

void FlexSensors::read() {
    channel[0] = analogRead(A0);
    channel[1] = analogRead(A1);
    channel[2] = analogRead(A2);
    channel[3] = analogRead(A3);
    channel[4] = analogRead(A6);
    channel[5] = analogRead(A7);
}

//------------------------------------------------------------------------------
// End of file