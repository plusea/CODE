// WISH LAB CODE: "Umbrella that makes sound when it rains"
// code for ATtiny45 or 85
// reads analog value from raindrops and plays a different note depending on which sensor was triggered
// also lights up LED light to corresponding note

int ledPin1 = 3;
int ledPin2 = 0;
int speakerPin = 1;
int sensorPin1 = 2; // ADC 2, digital Pin 4
int sensorPin2 = 1; // ADC 1, digital Pin 2
int sensorValue1;
int sensorValue2;

#include "pitches.h"

void setup() {
  pinMode(speakerPin, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  // sensor pins:
  pinMode(4, INPUT);
  digitalWrite(4, HIGH); //set internal pull-up
  pinMode(2, INPUT);
  digitalWrite(2, HIGH); //set internal pull-up
}

void loop() {
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);
  if(sensorValue1 < 900) makeNoise(speakerPin, NOTE_D8, 400, ledPin1);
  if(sensorValue2 < 900) makeNoise(speakerPin, NOTE_C7, 400, ledPin2);
}


void makeNoise(unsigned char pin, int frequencyInHertz, long timeInMilliseconds, int LEDpin) { 	 
  int x; 	 
  long delayAmount = (long)(1000000/frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
  digitalWrite(LEDpin, HIGH);
  for (x=0;x<loopTime;x++) 	 
  { 	 
    digitalWrite(pin,HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(pin,LOW);
    delayMicroseconds(delayAmount);
  } 	 
  digitalWrite(LEDpin, LOW);
} 


