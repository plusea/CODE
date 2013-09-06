// UdK - DRL - EIT
// code for 6-segment resistive sensing ball
// reads 6 analo ginput pins
// does smoothing on input by averaging over time
// prints sensor values to serial port

#include "pitches.h"
int inByte = 'x';
const int numReadings = 10;
const int numSensors = 6;
int readings[numSensors][numReadings];      // the readings from the analog input
int nR = 0;                  // the index of the current reading
int nS = 0;                  // the index of the current sensor
int total[numSensors];                  // the running total for each sensor
int average[numSensors];                // the average for each sensor

int sensorValues[numSensors];                // the average for each sensor
int threshold = 250;
int speakerPin = 8;
int speakerGND = 5;
int ledPin = 10;
int ledGND = 11;
int onPin = 13;
int notes[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5};

void setup()
{
  pinMode(A0, INPUT_PULLUP); 
  pinMode(A1, INPUT_PULLUP); 
  pinMode(A2, INPUT_PULLUP); 
  pinMode(A3, INPUT_PULLUP); 
  pinMode(A4, INPUT_PULLUP); 
  pinMode(A5, INPUT_PULLUP); 
  pinMode(speakerPin, OUTPUT);
  pinMode(speakerGND, OUTPUT);
  digitalWrite(speakerGND, LOW);
  pinMode(ledPin, OUTPUT);
  pinMode(ledGND, OUTPUT);
  digitalWrite(ledGND, LOW);
  digitalWrite(onPin, HIGH);

  //Serial.begin(9600);  //USB
  Serial.begin(57600);  //Bluetooth module
  Serial.println("starting...");

  for (nS = 0; nS < numSensors; nS++){
    for (nR = 0; nR < numReadings; nR++){
      readings[nS][nR] = 0;  
    }    
  }
  noTone(speakerPin);
}



void loop() {
  if (Serial.available() > 0) {
    inByte = Serial.read();
  }


  for (nR = 0; nR < numReadings; nR++){  // advance to the next position in the array
    for (nS = 0; nS < numSensors; nS++){  // advance to the next sensor
      total[nS] = total[nS] - readings[nS][nR];  // subtract the last reading      
      readings[nS][nR] = analogRead(nS);  // read from the sensor
      total[nS] = total[nS] + readings[nS][nR];     // add the reading to the total 
      average[nS] = total[nS] / numReadings;   // calculate the average      
    }
  }

  if(inByte == 'p'){    // if ZERO then send serial data
    serialPrint();
    noTone(speakerPin);
  }


  else { // otherwise play tones thorugh on-board speaker
    for (nS = 0; nS < numSensors; nS++){  // advance to the next sensor
      if(average[nS] < threshold){
        digitalWrite(ledPin, HIGH);
        tone(speakerPin, notes[nS]);
        delay(200); 
      }
      else {
        digitalWrite(ledPin,LOW);
        noTone(speakerPin);
      }
    }
    Serial.println(inByte);
  } 


}



void serialPrint(){
  for (nS = 0; nS < numSensors; nS++){  // advance to the next sensor
    Serial.print(average[nS]);
    if(nS<numSensors-1)Serial.print(",");
  }
  Serial.println();
  delay(10);
}



















