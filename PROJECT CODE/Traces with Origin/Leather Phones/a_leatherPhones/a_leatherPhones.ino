// code for speakerPhones
#include "pitches.h"
#define speakerPinR 2
#define speakerPinL 3
#define sensorPin 2

void setup() {
  pinMode(speakerPinR, OUTPUT);  
  pinMode(speakerPinL, OUTPUT);
  pinMode(sensorPin, INPUT);  
  digitalWrite(4, HIGH);
}

void loop() {
  int  lightValue = analogRead(sensorPin);
  lightValue = map(lightValue, 0, 1023, 1000, 5000);
  myTone(speakerPinL, lightValue, 100);
}

void myTone (unsigned char speaker, int frequencyInHertz, long timeInMilliseconds)     // the sound producing function
{ 	 
  int x; 	 
  long delayAmount = (long)(1000000/frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
  for (x=0;x<loopTime;x++) 	 
  { 	 
    digitalWrite(speaker,HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(speaker,LOW);
    delayMicroseconds(delayAmount);
  } 	 
} 
