// code for textiles sensor demos

#include <SoftwareSerial.h>

SoftwareSerial mySerial(5, 0); // RX, TX

#define gridPin1 1
#define gridPin2 2
#define gridPin3 3
#define gridPin4 4
#define speakerPin 0

int sensorValueA = 0;
int sensorValueB = 0;
int sensorValueC = 0;


void setup() {
  pinMode(speakerPin, OUTPUT);  

  //  mySerial.begin(9600);
  //  mySerial.println("Hello, world?");

  myTone(speakerPin, 2093, 200);
  myTone(speakerPin, 2349, 200);
  myTone(speakerPin, 2637, 200);
}




void loop() {

  //// READ SENSOR A ////
  pinMode(4, OUTPUT);  // GND
  digitalWrite(4, LOW);
  pinMode(3, INPUT);
  digitalWrite(3, HIGH);  //turn on pull-up
  pinMode(2, INPUT);
  pinMode(1, INPUT);
  delay(2);
  sensorValueA = analogRead(3);

  //// READ SENSOR B ////
  pinMode(2, OUTPUT);  // GND
  digitalWrite(2, LOW);
  // keep pin 3 as input with pull-up on
  pinMode(4, INPUT);
  pinMode(1, INPUT);
  delay(2);
  sensorValueB = analogRead(3);

  //// READ SENSOR C ////
  pinMode(1, OUTPUT);  // GND
  digitalWrite(1, LOW);
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);  //turn on pull-up
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  delay(2);
  sensorValueC = analogRead(1);

  //  mySerial.print(sensorValueA);
  //  mySerial.print(", ");
  //  mySerial.print(sensorValueC);
  //  mySerial.print(", ");
  //  mySerial.print(sensorValueB);
  //  mySerial.println();

  if(sensorValueA < 100) myTone(speakerPin, 2093, 500);
  if(sensorValueB < 100) myTone(speakerPin, 2349, 500);
  if(sensorValueC < 100) myTone(speakerPin, 2637, 500);

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








