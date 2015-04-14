/*
    MPU6000.h
    Author: Seb Madgwick
*/

#ifndef MPU6000_h
#define MPU6000_h

//------------------------------------------------------------------------------
// Definitions

typedef union {
    struct {
        int accX;
        int accY;
        int accZ;
        int gyrX;
        int gyrY;
        int gyrZ;
    };
    struct {
        char accXByteL;
        char accXByteH;
        char accYByteL;
        char accYByteH;
        char accZByteL;
        char accZByteH;
        char gyrXByteL;
        char gyrXByteH;
        char gyrYByteL;
        char gyrYByteH;
        char gyrZByteL;
        char gyrZByteH;
    };
} MPU6000Sensors;

//------------------------------------------------------------------------------
// Class declaration

class MPU6000 {
    public:
        static MPU6000Sensors sensors;
        static void init();
        static void read();

    private:
        static char spiRead(const char reg);
        static void spiWrite(const char reg, const char regData);
};

#endif

//------------------------------------------------------------------------------
// End of file
