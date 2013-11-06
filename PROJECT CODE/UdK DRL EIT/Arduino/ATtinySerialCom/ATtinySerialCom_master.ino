// code for textiles sensor demos

#include <SoftwareSerial.h>

SoftwareSerial mySerial(1, 0); // RX, TX

#define speakerPin 2
#define sensorPin 4
#define redPin 1
#define bluePin 0
#define greenPin 3
int sensorValue = 0;


void setup() {
  pinMode(speakerPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);

  mySerial.begin(9600);
  mySerial.println("Hello, world?");

  // speaker and LED test sequence
  rgbLED(0,255,1);
  myTone(speakerPin, 2093, 200);
  rgbLED(255,0,1);
  myTone(speakerPin, 2349, 200);
  rgbLED(255,255,0);
  myTone(speakerPin, 2637, 200);
}



void rgbLED(int red, boolean blue, int green){
  digitalWrite(greenPin, green);
  analogWrite(redPin, red);
  analogWrite(bluePin, blue);
}



void loop() {
  sensorValue = analogRead(2);

  //mySerial.println(sensorValue);

  if(sensorValue > 70 && sensorValue < 100) {
    rgbLED(0,255,1);
    myTone(speakerPin, 1250, 500);
  }
  if(sensorValue > 130 && sensorValue < 170) {
    rgbLED(255,0,1); 
    myTone(speakerPin, 1110, 500);
  }
  if(sensorValue > 190 && sensorValue < 230) {
    rgbLED(255,255,0); 
    myTone(speakerPin, 1050, 500);
  }
  if(sensorValue > 250 && sensorValue < 280) {
    rgbLED(230,255,1); 
    myTone(speakerPin, 940, 500);
  }
  if(sensorValue > 300 && sensorValue < 330) {
    rgbLED(230,0,0); 
    myTone(speakerPin, 837, 500);
  }
  
  if(sensorValue < 70 || sensorValue > 330) rgbLED(255,255,1); 

}


void myTone (unsigned char speaker, int frequencyInHertz, long timeInMilliseconds) { 	  
  long delayAmount = (long)(1000000/frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
  for (int x=0;x<loopTime;x++) 	 
  { 	 
    digitalWrite(speaker,HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(speaker,LOW);
    delayMicroseconds(delayAmount);
  } 
  digitalWrite(speakerPin, LOW);	 
} 










