/*
    FlexSensors.h
    Author: Seb Madgwick
*/

#ifndef FlexSensors_h
#define FlexSensors_h

//------------------------------------------------------------------------------
// Class declaration

class FlexSensors {
    public:
        static int channel[6];
        static void init();
        static void read();
};

#endif

//------------------------------------------------------------------------------
// End of file
