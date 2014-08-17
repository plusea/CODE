// code for hahnentritt stulpe by nathalie
// runs on attiny45
// reads two analog inputs from knit sensors
// sends sensor data over serial port to processing sketch
// triggers warning beep sound if both sensor values remain above their thresholds for certain period of time

//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(5, 0); // RX, TX

#include <SendOnlySoftwareSerial.h>
SendOnlySoftwareSerial mySerial (0);  // Tx pin 

//// variables to be changed: /////
int threshold1 = 50;
int threshold2 = 300;
int triggerTime = 1000;
//////////////////////////////////

int speakerPin = 2;
int ledPinGreen = 1;
//int ledPinRed = 2;
int inByte;
boolean isOverThreshold = false;
int timeCount;


void setup() {
  // set the data rate for the SoftwareSerial port
  mySerial.begin(57600);
  mySerial.println("starting...");
  pinMode(speakerPin, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  //pinMode(ledPinRed, OUTPUT);
  pinMode(3, INPUT);  // analog 3
  pinMode(4, INPUT);  // analog 2
}


void loop() {
  int sensorValue1 = analogRead(2);
  int sensorValue2 = analogRead(3);
  mySerial.print(sensorValue1);
  mySerial.print(", ");
  mySerial.println(sensorValue2);
  delay(50);
  //mySerial.print(", ");
  //mySerial.println(timeCount);

  if(sensorValue1 > threshold1) digitalWrite(ledPinGreen, HIGH);
  else digitalWrite(ledPinGreen, LOW);
  //if(sensorValue2 > threshold2) digitalWrite(ledPinRed, HIGH);
  //else digitalWrite(ledPinRed, LOW);

  // if both values are over the threshold
  if(sensorValue1 > threshold1 && sensorValue2 > threshold2) {
      timeCount++;                     // take note of the activation time
    }
    if(sensorValue1 <= threshold1 || sensorValue2 <= threshold2) {                                   // if the values are under the threshold
      timeCount=0;
    }
    
    if(timeCount >= triggerTime) {            // if the activation time was more than 5 secs ago
      //mySerial.println("Ring Ring");         // ring the bell
      playNote(speakerPin, 1000, 500); 
    }
  }



void playNote (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds)     // the sound producing function
{	 
  int x;	 
  long delayAmount = (long)(1000000/frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
  for (x=0;x<loopTime;x++)	 
  {	 
    digitalWrite(speakerPin,HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(speakerPin,LOW);
    delayMicroseconds(delayAmount);
  }	 
}







