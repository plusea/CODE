/*
||
|| @author Alexander Brevig
|| @version 1.0
||
*/

#ifndef CHARLIEPLEX_H
#define CHARLIEPLEX_H

#include <WProgram.h>

struct CharliePin {
	byte vcc;
	byte gnd;
};

typedef CharliePin charliePin;

class Charlieplex {

#define INDEX 1
#define NUMBER_OF_STATUSES ((_numberOfPins*_numberOfPins)-_numberOfPins)

public:
	Charlieplex(byte* userPins,byte numberOfUserPins);
	
	void charlieWrite(charliePin pin,bool state);
	
	void setVcc(byte pin);
	void setGnd(byte pin);
	
	void clear();
	
private:
	byte numberOfPins;
	byte* pins;
};

#endif

