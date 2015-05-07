/*
    I2CBus.cpp
    Author: Seb Madgwick
*/

//------------------------------------------------------------------------------
// Includes

#include <Arduino.h>
#include "HMC5883Ldefs.h"
#include "I2CBus.h"
#include <Wire.h>

//------------------------------------------------------------------------------
// Definitions

#define HMC_ADDR    0x1E   // why is HMC5883L address not 0x3C as per datasheet?
#define MINM_ADDR   0x09

//------------------------------------------------------------------------------
// Variables

Magnetometer I2CBus::magnetometer;

//------------------------------------------------------------------------------
// Methods

void I2CBus::init() {

    // Init I2C
    Wire.begin();
    delay(10);

    // Setup HMC5883
    Wire.beginTransmission(HMC_ADDR);
    Wire.write(CONFIG_REG_A);
    Wire.write(RATE_75HZ);
    Wire.write(GAIN_4P7G);
    Wire.write(MODE_CONT);  // write to this register else HMC5883 initialisation may fail
    Wire.endTransmission();

    // Setup up MinM
    Wire.beginTransmission(MINM_ADDR);
    Wire.write('o');    // stop script
    Wire.endTransmission();
    Wire.beginTransmission(MINM_ADDR);
    Wire.write('n');    // set RGB
    Wire.write(0);
    Wire.write(0);
    Wire.write(0);
    Wire.endTransmission();
}

void I2CBus::readMagnetometer() {
    Wire.beginTransmission(HMC_ADDR);
    Wire.write(DOUT_X_MSB);
    Wire.endTransmission();
    Wire.requestFrom(HMC_ADDR, 6);
    magnetometer.xByteH = Wire.read();
    magnetometer.xByteL = Wire.read();
    magnetometer.zByteH = Wire.read();
    magnetometer.zByteL = Wire.read();
    magnetometer.yByteH = Wire.read();
    magnetometer.yByteL = Wire.read();
    Wire.endTransmission();
    magnetometer.x = -magnetometer.x;   // correct for physical misalignment
    magnetometer.y = -magnetometer.y;
}

void I2CBus::setRGB(const unsigned char red, const unsigned char green, const unsigned char blue) {
    Wire.beginTransmission(MINM_ADDR);
    Wire.write('n');    // use 'c' to fade transitions
    Wire.write(red);
    Wire.write(green);
    Wire.write(blue);
    Wire.endTransmission();
}

//------------------------------------------------------------------------------
// End of file
