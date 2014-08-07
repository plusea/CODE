// code for hahnentritt stulpe by hannah
// runs on attiny45
// reads two analog inputs from knit sensors
// sends sensor data over serial port

//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(0,1); // RX, TX

#include <SendOnlySoftwareSerial.h>
SendOnlySoftwareSerial mySerial (1);  // Tx pin 

int speakerPin = 4;
//int ledPinGreen = 1;  //COMMENT OUT FOR SOFTSERIAL!!!
int ledPinBlue = 0;
int sensor1BottomPin = 2; //ADC1
int sensor2TopPin = 3; //ADC3

//// variables to be changed: /////
int threshold1 = 50;
int threshold2 = 300;
int triggerTime = 1000;
//////////////////////////////////

boolean isOverThreshold = false;
int timeCount;
   
void setup() {
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  //mySerial.begin(57600);
  mySerial.println("starting...");
  pinMode(speakerPin, OUTPUT);
  //pinMode(ledPinGreen, OUTPUT);  //COMMENT OUT FOR SOFTSERIAL!!!
  pinMode(ledPinBlue, OUTPUT);
  //digitalWrite(ledPinGreen, HIGH);  //off, COMMENT OUT FOR SOFTSERIAL!!!
  digitalWrite(ledPinBlue, HIGH);  //off
  pinMode(2, INPUT); //ADC1
  pinMode(3, INPUT); //ADC3
  //digitalWrite(2, HIGH);
  //digitalWrite(3, HIGH);
}


void loop() {
  int sensorValue1Bottom = analogRead(1);
  int sensorValue2Top = analogRead(3);
  mySerial.print(sensorValue1Bottom);
  mySerial.print(", ");
  mySerial.println(sensorValue2Top);
  delay(10);

//  if(sensorValue1Bottom > threshold1) digitalWrite(ledPinGreen, LOW);
//  else digitalWrite(ledPinGreen, HIGH);
//  if(sensorValue2Top > threshold2) digitalWrite(ledPinBlue, LOW);
//  else digitalWrite(ledPinBlue, HIGH);
//
//  // if both values are over the threshold
//  if(sensorValue1Bottom > threshold1 && sensorValue2Top > threshold2) {
//      timeCount++;                     // take note of the activation time
//    }
//    if(sensorValue1Bottom <= threshold1 || sensorValue2Top <= threshold2) {                                   // if the values are under the threshold
//      timeCount=0;
//    }
//    
//    if(timeCount >= triggerTime) {            // if the activation time was more than 5 secs ago
//      mySerial.println("Ring Ring");         // ring the bell
//      playNote(speakerPin, 1000, 500); 
//    }
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







