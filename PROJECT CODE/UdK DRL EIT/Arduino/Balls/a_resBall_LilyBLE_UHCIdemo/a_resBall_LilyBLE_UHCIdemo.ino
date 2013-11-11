// UdK - DRL - EIT
// code for 6-segment resistive sensing ball
// reads 6 analog input pins and takes average
// when under threshold light comes on

#include "pitches.h"

////// SET THRESHOLD HERE!!! //////
int threshold = 4000;
///////////////////////////////////

const int numSensors = 6;
int readings[numSensors];      // the readings from the analog inputs
int totalNS;
int ledPin = 10;
int ledGND = 11;
int onPin = 13;

void setup()
{
  pinMode(A0, INPUT_PULLUP); 
  pinMode(A1, INPUT_PULLUP); 
  pinMode(A2, INPUT_PULLUP); 
  pinMode(A3, INPUT_PULLUP); 
  pinMode(A4, INPUT_PULLUP); 
  pinMode(A5, INPUT_PULLUP); 
  pinMode(ledPin, OUTPUT);
  pinMode(ledGND, OUTPUT);
  digitalWrite(ledGND, LOW);
  digitalWrite(onPin, HIGH);
  Serial.begin(57600);
  Serial.println("starting...");
}

void loop() {
  for (int nS = 0; nS < numSensors; nS++) readings[nS] = analogRead(nS);  // read from the sensor
  totalNS = readings[0] + readings[1] + readings[2] + readings[3] + readings[4] + readings[5]; 
  if(totalNS < threshold) digitalWrite(ledPin, HIGH);
  else digitalWrite(ledPin,LOW);
  Serial.println(totalNS);
  delay(2);
}

























