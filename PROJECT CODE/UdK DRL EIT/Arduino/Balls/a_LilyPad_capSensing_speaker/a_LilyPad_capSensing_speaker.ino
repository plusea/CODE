// capacitive sensing on lilypad simple

// readCapacitivePin
// Input: Arduino pin number
// Output: A number, from 0 to 17 expressing
// how much capacitance is on the pin
// When you touch the pin, or whatever you have
// attached to it, the number will get higher
// See more at: http://lilypadarduino.org/?p=1798#sthash.JoCMRY7h.dpuf

#include "pitches.h"

int capPin[9] = {
  5,6,9,10,11,16,17,18,19};
int notes[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5};
int capValue[9];
int speakerPin = 15;
int ledPin = 13;

void setup()
{ 
  Serial.begin(57600);
  pinMode(speakerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin,LOW);
}



void loop() // run over and over
{
  for(int i = 0; i<9; i++){
    capValue[i] = readCapacitivePin(capPin[i]);
    Serial.print(capValue[i]);
    if(i<9-1) Serial.print(",");

    if(capValue[i] > 1) {
      digitalWrite(ledPin, HIGH);
      tone(speakerPin, notes[i]);
      delay(200); 
    }
    else {
      digitalWrite(ledPin,LOW);
      noTone(speakerPin);
    }
  }

  Serial.println();
} 








