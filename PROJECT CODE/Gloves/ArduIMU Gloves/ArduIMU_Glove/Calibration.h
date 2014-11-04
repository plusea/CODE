/*
    Calibration.c
    Author: Seb Madgwick
*/

#ifndef Calibration_h
#define Calibration_h

//------------------------------------------------------------------------------
// Definitions

typedef enum {
    REG_IS_BLANK,
    REG_GYR_SENS_X,
    REG_GYR_SENS_Y,
    REG_GYR_SENS_Z,
    REG_GYR_BIAS_X,
    REG_GYR_BIAS_Y,
    REG_GYR_BIAS_Z,
    REG_ACC_SENS_X,
    REG_ACC_SENS_Y,
    REG_ACC_SENS_Z,
    REG_ACC_BIAS_X,
    REG_ACC_BIAS_Y,
    REG_ACC_BIAS_Z,
    REG_MAG_SOFT_XX,
    REG_MAG_SOFT_XY,
    REG_MAG_SOFT_XZ,
    REG_MAG_SOFT_YX,
    REG_MAG_SOFT_YY,
    REG_MAG_SOFT_YZ,
    REG_MAG_SOFT_ZX,
    REG_MAG_SOFT_ZY,
    REG_MAG_SOFT_ZZ,
    REG_MAG_HARD_X,
    REG_MAG_HARD_Y,
    REG_MAG_HARD_Z,
    NUM_REGISTERS
} RegisterAddress;

//------------------------------------------------------------------------------
// Class declaration

class Calibration {
    public:
        static int reg[NUM_REGISTERS];  // calibration registers
        static float gyrX, gyrY, gyrZ;  // calibrated gyroscope data (0.1 dps)
        static float accX, accY, accZ;  // calibrated accelerometer data (mg)
        static float magX, magY, magZ;  // calibrated magnetometer data (mGa)
        static void init();
        static void update();
        static void saveToEEPROM();

    private:
        static float grx, gry, grz; // gyroscope sensitivity reciprocal (0.1 dps/lsb)
        static float gbx, gby, gbz; // gyroscope bias (lsb)
        static float arx, ary, arz; // accelerometer sensitivity reciprocal (mg/lsb)
        static float abx, aby, abz; // accelerometer bias (lsb)
        static float sxx, sxy, sxz; // soft-iron x-axis parameters
        static float syx, syy, syz; // soft-iron y-axis parameters
        static float szx, szy, szz; // soft-iron z-axis parameters
        static float hx, hy, hz;    // hard-iron parameters (mGa)
};

#endif

//------------------------------------------------------------------------------
// End of file
