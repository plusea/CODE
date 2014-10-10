/*
||
|| @author Alexander Brevig
|| @version 1.0
||
*/

#include "Charlieplex.h"

Charlieplex::Charlieplex(byte* userPins,byte numberOfUserPins){
	pins = userPins;
	numberOfPins = numberOfUserPins;
	clear();
}

void Charlieplex::charlieWrite(charliePin pin, bool state){
	if(state){
		setVcc(pin.vcc);
		setGnd(pin.gnd);
	}else{
		pinMode(pin.vcc,INPUT);
	}
}

//set a pin HIGH 
void Charlieplex::setVcc(byte pin){
	pinMode( pins[pin] , OUTPUT );
	digitalWrite( pins[pin] , HIGH );
}

//set a pin LOW 
void Charlieplex::setGnd(byte pin){
	pinMode( pins[pin] , OUTPUT );
	digitalWrite( pins[pin] , LOW );
}

//set all as input
void Charlieplex::clear(){
	for (byte i=0; i<numberOfPins; i++){
		pinMode( pins[i] , INPUT);
	}
}