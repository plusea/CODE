// code for ATtiny45 or 85
// reads digital value and plays melody when triggered
// reads analog value and maps the value directly to a frequency

int speakerPin = 0;
int sensorPin = 3; // digital Pin 3 = ADC 3
int sensorValue = 0;
int buttonValue = 0;

#include "pitches.h"

void setup() {
  pinMode(speakerPin, OUTPUT);
  pinMode(sensorPin, INPUT_PULLUP);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  if(sensorValue < 900) makeNoise(speakerPin, sensorValue*3, 100);
  //if(sensorValue < 700) playMelody(speakerPin);
}


void makeNoise(unsigned char pin, int frequencyInHertz, long timeInMilliseconds) { 	 
  int x; 	 
  long delayAmount = (long)(1000000/frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
  for (x=0;x<loopTime;x++) 	 
  { 	 
    digitalWrite(pin,HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(pin,LOW);
    delayMicroseconds(delayAmount);
  } 	 
} 


void playMelody(unsigned char pin) {
  // Brahms' Lullaby (cradle song)
  makeNoise(pin, NOTE_E5, 300);
  delay(10);  
  makeNoise(pin, NOTE_E5, 300);
  delay(10);  
  makeNoise(pin, NOTE_G5, 600);
  delay(100); 
  makeNoise(pin, NOTE_E5, 300);
  delay(10);  
  makeNoise(pin, NOTE_E5, 300);
  delay(10);  
  makeNoise(pin, NOTE_G5, 600);
  delay(100); 
  makeNoise(pin, NOTE_E5, 300);
  delay(50);  
  makeNoise(pin, NOTE_G5, 300);
  delay(10);  
  makeNoise(pin, NOTE_C6, 500);
  delay(100);  
  makeNoise(pin, NOTE_B5, 600);
  delay(100);  
  makeNoise(pin, NOTE_A5, 400);
  delay(100); 
  makeNoise(pin, NOTE_A5, 500);
  delay(100);   
  makeNoise(pin, NOTE_G5, 600);
  delay(200); 
  makeNoise(pin, NOTE_D5, 300);
  delay(50);  
  makeNoise(pin, NOTE_E5, 300);
  delay(100); 
  makeNoise(pin, NOTE_F5, 400);
  delay(100);
  makeNoise(pin, NOTE_D5, 600);
  delay(200); 
  makeNoise(pin, NOTE_D5, 300);
  delay(100);  
  makeNoise(pin, NOTE_E5, 300);
  delay(100);  
  makeNoise(pin, NOTE_F5, 600);
  delay(200); 
  makeNoise(pin, NOTE_D5, 400);
  delay(100); 
  makeNoise(pin, NOTE_F5, 400);
  delay(100); 
  makeNoise(pin, NOTE_B5, 300);
  delay(10); 
  makeNoise(pin, NOTE_A5, 300);
  delay(100);
  makeNoise(pin, NOTE_G5, 500);
  delay(200); 
  makeNoise(pin, NOTE_B5, 600);
  delay(100); 
  makeNoise(pin, NOTE_C6, 800); 
}











