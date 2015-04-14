/*
    HMC5883Ldefs.h
    Author: Seb Madgwick

    Definitions for Honeywell HMC5883L register addresses and values.
*/

#ifndef HMC5883Ldefs_h
#define HMC5883Ldefs_h

#define HMC5883LaddrW   0x3C    // I2C address
#define HMC5883LaddrR   0x3D

#define CONFIG_REG_A    0x00    // registers
#define CONFIG_REG_B    0x01
#define MODE_REG        0x02
#define DOUT_X_MSB      0x03
#define DOUT_X_LSB      0x04
#define DOUT_Y_MSB      0x05
#define DOUT_Y_LSB      0x06
#define DOUT_Z_MSB      0x07
#define DOUT_Z_LSB      0x08
#define STAT_REG        0x09
#define ID_REG_A        0x0A
#define ID_REG_B        0x0B
#define ID_REG_C        0x0C

#define MEAS_NORM       0b00000000  // CONFIG_REG_A
#define MEAS_POS_BIAS   0b00000001
#define MEAS_NEG_BIAS   0b00000010
#define RATE_0P75HZ     0b00000000
#define RATE_1P5HZ      0b00000100
#define RATE_3HZ        0b00001000
#define RATE_7P5HZ      0b00001100
#define RATE_15HZ       0b00010000
#define RATE_30HZ       0b00010100
#define RATE_75HZ       0b00011000

#define GAIN_0P88G      0b00000000  // CONFIG_REG_B
#define GAIN_1P3G       0b00100000
#define GAIN_1P9G       0b01000000
#define GAIN_2P5G       0b01100000
#define GAIN_4G         0b10000000
#define GAIN_4P7G       0b10100000
#define GAIN_5P6G       0b11000000
#define GAIN_8P1G       0b11100000

#define MODE_CONT       0b00000000  // MODE_REG
#define MODE_SINGLE     0b00000001
#define MODE_IDLE       0b00000010

#endif

//------------------------------------------------------------------------------
// End of file
