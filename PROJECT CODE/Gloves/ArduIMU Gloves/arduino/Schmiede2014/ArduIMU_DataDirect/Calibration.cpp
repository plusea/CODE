/*
    Calibration.cpp
    Author: Seb Madgwick
*/

//------------------------------------------------------------------------------
// Includes

#include "Calibration.h"
#include <EEPROM.h>
#include "I2CBus.h"
#include "MPU6000.h"

//------------------------------------------------------------------------------
// Definitions

typedef union {
    int intVal;
    struct {
        char lsb;
        char msb;
    };
} IntUnion;

//------------------------------------------------------------------------------
// Variables

// Public
int Calibration::reg[NUM_REGISTERS];                            // calibration registers
float Calibration::gyrX, Calibration::gyrY, Calibration::gyrZ;  // calibrated gyroscope data (0.1 dps)
float Calibration::accX, Calibration::accY, Calibration::accZ;  // calibrated accelerometer data (mg)
float Calibration::magX, Calibration::magY, Calibration::magZ;  // calibrated magnetometer data (mGa)

// Private
float Calibration::grx, Calibration::gry, Calibration::grz; // gyroscope sensitivity reciprocal (0.1 dps/lsb)
float Calibration::gbx, Calibration::gby, Calibration::gbz; // gyroscope bias (lsb)
float Calibration::arx, Calibration::ary, Calibration::arz; // accelerometer sensitivity reciprocal (mg/lsb)
float Calibration::abx, Calibration::aby, Calibration::abz; // accelerometer bias (lsb)
float Calibration::sxx, Calibration::sxy, Calibration::sxz; // soft-iron x-axis parameters
float Calibration::syx, Calibration::syy, Calibration::syz; // soft-iron y-axis parameters
float Calibration::szx, Calibration::szy, Calibration::szz; // soft-iron z-axis parameters
float Calibration::hx, Calibration::hy, Calibration::hz;    // hard-iron parameters (mGa)

//------------------------------------------------------------------------------
// Methods

void Calibration::init() {

    // Load all registers from EEPROM
    for(int address = 0; address < NUM_REGISTERS; address++) {
        IntUnion intUnion;
        intUnion.lsb = EEPROM.read(2 * address);
        intUnion.msb = EEPROM.read((2 * address) + 1);
        reg[address] = intUnion.intVal;
    }

    // Check if registers are blank
    if(reg[REG_IS_BLANK] != 0) {

        // Load defaults
        reg[REG_IS_BLANK]       = 0;
        reg[REG_GYR_SENS_X]     = 16400;    // 0.001 lsb/dps
        reg[REG_GYR_SENS_Y]     = 16400;
        reg[REG_GYR_SENS_Z]     = 16400;
        reg[REG_GYR_BIAS_X]     = 0;        // 0.1 lsb
        reg[REG_GYR_BIAS_Y]     = 0;
        reg[REG_GYR_BIAS_Z]     = 0;
        reg[REG_ACC_SENS_X]     = 20480;    // 0.1 lsb/g
        reg[REG_ACC_SENS_Y]     = 20480;
        reg[REG_ACC_SENS_Z]     = 20480;
        reg[REG_ACC_BIAS_X]     = 0;        // 0.1 lsb
        reg[REG_ACC_BIAS_Y]     = 0;
        reg[REG_ACC_BIAS_Z]     = 0;
        reg[REG_MAG_SOFT_XX]    = 10000;    // 0.0001
        reg[REG_MAG_SOFT_XY]    = 0;
        reg[REG_MAG_SOFT_XZ]    = 0;
        reg[REG_MAG_SOFT_YX]    = 0;
        reg[REG_MAG_SOFT_YY]    = 10000;
        reg[REG_MAG_SOFT_YZ]    = 0;
        reg[REG_MAG_SOFT_ZX]    = 0;
        reg[REG_MAG_SOFT_ZY]    = 0;
        reg[REG_MAG_SOFT_ZZ]    = 10000;
        reg[REG_MAG_HARD_X]     = 0;        // 0.1 mGa
        reg[REG_MAG_HARD_Y]     = 0;
        reg[REG_MAG_HARD_Z]     = 0;

        // Save defaults to EEPROM
        saveToEEPROM();
    }

    // Create calibration parameters
    grx = 10000.0f / (float)reg[REG_GYR_SENS_X];
    gry = 10000.0f / (float)reg[REG_GYR_SENS_Y];
    grz = 10000.0f / (float)reg[REG_GYR_SENS_Z];
    gbx = (1.0f / 10.0f) * (float)reg[REG_GYR_BIAS_X];
    gby = (1.0f / 10.0f) * (float)reg[REG_GYR_BIAS_Y];
    gbz = (1.0f / 10.0f) * (float)reg[REG_GYR_BIAS_Z];
    arx = 10000.0f / (float)reg[REG_ACC_SENS_X];
    ary = 10000.0f / (float)reg[REG_ACC_SENS_Y];
    arz = 10000.0f / (float)reg[REG_ACC_SENS_Z];
    abx = (1.0f / 10.0f) * (float)reg[REG_ACC_BIAS_X];
    aby = (1.0f / 10.0f) * (float)reg[REG_ACC_BIAS_Y];
    abz = (1.0f / 10.0f) * (float)reg[REG_ACC_BIAS_Z];
    sxx = (1.0f / 10000.0f) * (float)reg[REG_MAG_SOFT_XX];
    sxy = (1.0f / 10000.0f) * (float)reg[REG_MAG_SOFT_XY];
    sxz = (1.0f / 10000.0f) * (float)reg[REG_MAG_SOFT_XZ];
    syx = (1.0f / 10000.0f) * (float)reg[REG_MAG_SOFT_YX];
    syy = (1.0f / 10000.0f) * (float)reg[REG_MAG_SOFT_YY];
    syz = (1.0f / 10000.0f) * (float)reg[REG_MAG_SOFT_YZ];
    szx = (1.0f / 10000.0f) * (float)reg[REG_MAG_SOFT_ZX];
    szy = (1.0f / 10000.0f) * (float)reg[REG_MAG_SOFT_ZY];
    szz = (1.0f / 10000.0f) * (float)reg[REG_MAG_SOFT_ZZ];
    hx = (1.0f / 10.0f) * (float)reg[REG_MAG_HARD_X];
    hy = (1.0f / 10.0f) * (float)reg[REG_MAG_HARD_Y];
    hz = (1.0f / 10.0f) * (float)reg[REG_MAG_HARD_Z];
}

void Calibration::update() {
    float magx, magy, magz;
    gyrX = grx * (MPU6000::sensors.gyrX - gbx);
    gyrY = gry * (MPU6000::sensors.gyrY - gby);
    gyrZ = grz * (MPU6000::sensors.gyrZ - gbz);
    accX = arx * (MPU6000::sensors.accX - abx);
    accY = ary * (MPU6000::sensors.accY - aby);
    accZ = arz * (MPU6000::sensors.accZ - abz);
    magx = (1000.0f / 390.0f) * I2CBus::magnetometer.x;
    magy = (1000.0f / 390.0f) * I2CBus::magnetometer.y;
    magz = (1000.0f / 390.0f) * I2CBus::magnetometer.z;
    magX = sxx * magx + sxy * magy + sxz * magz - hx;
    magY = syx * magx + syy * magy + syz * magz - hy;
    magZ = szx * magx + szy * magy + szz * magz - hz;
}

void Calibration::saveToEEPROM() {
    for(int address = 0; address < NUM_REGISTERS; address++) {
        IntUnion intUnion;
        intUnion.intVal = reg[address];
        EEPROM.write(2 * address, intUnion.lsb);
        EEPROM.write((2 * address) + 1, intUnion.msb);
    }
}

//------------------------------------------------------------------------------
// End of file
