// capacitive sensing on lilypad simple

// readCapacitivePin
// Input: Arduino pin number
// Output: A number, from 0 to 17 expressing
// how much capacitance is on the pin
// When you touch the pin, or whatever you have
// attached to it, the number will get higher
// See more at: http://lilypadarduino.org/?p=1798#sthash.JoCMRY7h.dpuf

#include "pitches.h"

int capPin[3] = {
  6,9,10};
int ledPin[3] = {
  16,17,18};
int notes[] = {
  NOTE_C4, NOTE_D4, NOTE_E4};
int capValue[3];
#define speakerPin 5
#define lightSensorPin A5

void setup()
{ 
  Serial.begin(9600);
  pinMode(lightSensorPin, INPUT_PULLUP);
  pinMode(speakerPin, OUTPUT);
  for(int i = 0; i<3; i++){
    pinMode(ledPin[i], OUTPUT);
    digitalWrite(ledPin[i],LOW);
  }
}



void loop() // run over and over
{
  int lightValue = analogRead(lightSensorPin);
  Serial.print(lightValue);
  Serial.print(",");
  
  if(lightValue > 300) {
    lightValue = map(lightValue, 300, 1023, 300, 3000);
    tone(speakerPin, lightValue);
  }
  else noTone(speakerPin);
  
  for(int i = 0; i<3; i++){
    capValue[i] = readCapacitivePin(capPin[i]);
    Serial.print(capValue[i]);
    if(i<3-1) Serial.print(",");

    if(capValue[i] > 1) {
      digitalWrite(ledPin[i], HIGH);
      tone(speakerPin, notes[i]);
      delay(200); 
    }
    else {
      digitalWrite(ledPin[i],LOW);
      noTone(speakerPin);
    }
  }

  Serial.println();
} 










