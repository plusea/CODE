// SLAVE CODE //

#include <SoftwareSerial.h>

SoftwareSerial mySerial(1, 0); // RX, TX

#define redPin 2
#define bluePin 3
#define greenPin 4
byte colour;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  mySerial.begin(9600);
  //mySerial.println("Hello, world?");

  digitalWrite(redPin, HIGH);
  delay(1000);
  digitalWrite(greenPin, HIGH);
  delay(1000);
  digitalWrite(bluePin, HIGH);
  delay(1000);

  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}



void loop() {
  if (mySerial.available())
    colour = mySerial.read();
    mySerial.println(colour);
    
//  if(colour == 0) {
//    digitalWrite(redPin, LOW);
//    digitalWrite(greenPin, LOW);
//    digitalWrite(bluePin, LOW);
//  }

  if(colour == 1) {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
  }

  if(colour == 2) {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
  }

  if(colour == 3) {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
  }
}










