/*
    LEDs.h
    Author: Seb Madgwick
*/

#ifndef LEDs_h
#define LEDs_h

//------------------------------------------------------------------------------
// Class declaration

class LEDs {
    public:
        static void init();
        static void setRed(bool state);
        static void setBlue(bool state);
};

#endif

//------------------------------------------------------------------------------
// End of file
