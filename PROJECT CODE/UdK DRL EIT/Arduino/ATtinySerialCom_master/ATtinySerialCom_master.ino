// MASTER CODE //

#include <SoftwareSerial.h>

SoftwareSerial mySerial(1, 0); // RX, TX

#define redPin 2
#define bluePin 3
#define greenPin 4
byte sensorValue = 1;


void setup() {
  pinMode(redPin, INPUT);
  digitalWrite(redPin, HIGH);
  pinMode(bluePin, INPUT);
  digitalWrite(bluePin, HIGH);
  pinMode(greenPin, INPUT);
  digitalWrite(greenPin, HIGH);

  mySerial.begin(9600);
  //mySerial.println("Hello, world?");
}



void loop() {
//  if(digitalRead(redPin) == 0) sensorValue = 1;
//  else if(digitalRead(greenPin) == 0) sensorValue = 2;
//  else if(digitalRead(bluePin) == 0) sensorValue = 3;
//  else sensorValue == 0;
  mySerial.println(sensorValue);
  delay(10);
}
























void rgbLED(int red, boolean blue, int green){
  digitalWrite(greenPin, green);
  analogWrite(redPin, red);
  analogWrite(bluePin, blue);
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
  digitalWrite(speaker, LOW);	 
} 










