/*
    MPU6000.cpp
    Author: Seb Madgwick
*/

//------------------------------------------------------------------------------
// Includes

#include <Arduino.h>
#include "MPU6000.h"
#include "MPU6000defs.h"
#include <SPI.h>

//------------------------------------------------------------------------------
// Definitions

#define MPU6000_CS_PIN 4

//------------------------------------------------------------------------------
// Variables

MPU6000Sensors MPU6000::sensors;

//------------------------------------------------------------------------------
// Methods

void MPU6000::init() {

    // Init MPU6000 CS pin
    pinMode(MPU6000_CS_PIN, OUTPUT);
    digitalWrite(MPU6000_CS_PIN, HIGH);

    // Init SPI
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV16);   // SPI at 1Mhz (on 16Mhz clock)
    delay(10);

    // Setup MPU6000
    spiWrite(USER_CTRL, I2C_IF_DIS);
    spiWrite(PWR_MGMT_1, CLKSEL_PLLX);
    spiWrite(GYRO_CONFIG, FS_SEL_2000);
    spiWrite(ACCEL_CONFIG, AFS_SEL_16);
}

void MPU6000::read() {
    sensors.accXByteH = spiRead(ACCEL_XOUT_H);
    sensors.accXByteL = spiRead(ACCEL_XOUT_L);
    sensors.accYByteH = spiRead(ACCEL_YOUT_H);
    sensors.accYByteL = spiRead(ACCEL_YOUT_L);
    sensors.accZByteH = spiRead(ACCEL_ZOUT_H);
    sensors.accZByteL = spiRead(ACCEL_ZOUT_L);
    sensors.gyrXByteH = spiRead(GYRO_XOUT_H);
    sensors.gyrXByteL = spiRead(GYRO_XOUT_L);
    sensors.gyrYByteH = spiRead(GYRO_YOUT_H);
    sensors.gyrYByteL = spiRead(GYRO_YOUT_L);
    sensors.gyrZByteH = spiRead(GYRO_ZOUT_H);
    sensors.gyrZByteL = spiRead(GYRO_ZOUT_L);
}

char MPU6000::spiRead(const char addr) {
    char data;
    digitalWrite(MPU6000_CS_PIN, LOW);
    SPI.transfer(addr | 0x80);
    data = SPI.transfer(0);
    digitalWrite(MPU6000_CS_PIN, HIGH);
    return data;
}

void MPU6000::spiWrite(const char addr, const char data) {
    digitalWrite(MPU6000_CS_PIN, LOW);
    SPI.transfer(addr);
    SPI.transfer(data);
    digitalWrite(MPU6000_CS_PIN, HIGH);
}

//------------------------------------------------------------------------------
// End of file
