// UdK DRL EIT
// capacitive sensing on lilypad or lilypadBLE with resistive yarn

// readCapacitivePin
// Input: Arduino pin number
// Output: A number, from 0 to 17 expressing
// how much capacitance is on the pin
// When you touch the pin, or whatever you have
// attached to it, the number will get higher
// See more at: http://lilypadarduino.org/?p=1798#sthash.JoCMRY7h.dpuf

#include "pitches.h"

int capPin[6] = {
  5,19,17,11,10,6};
int notes[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4};
int capValue[6];
int speakerPin = 8;
int speakerGND = 5;
int onPin = 13;

void setup()
{ 
  Serial.begin(57600);
  pinMode(speakerPin, OUTPUT);
  pinMode(speakerGND, OUTPUT);
  digitalWrite(speakerGND, LOW);
  digitalWrite(onPin, HIGH);
}



void loop() // run over and over
{
  for(int i = 0; i<6; i++){
    capValue[i] = readCapacitivePin(capPin[i]);
    Serial.print(capValue[i]);
    if(i<6-1) Serial.print(",");

    if(capValue[i] > 1) {
      tone(speakerPin, notes[i]);
      delay(200); 
    }
    else {
      noTone(speakerPin);
    }
  }

  Serial.println();
} 









