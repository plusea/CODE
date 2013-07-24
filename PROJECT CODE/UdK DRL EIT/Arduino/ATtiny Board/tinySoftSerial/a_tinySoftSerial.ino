// software serial example for ATtiny!

#include <SoftwareSerial.h>

SoftwareSerial mySerial(1, 0); // RX, TX

void setup()
{
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("starting...");
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);
  pinMode(3, INPUT);
  digitalWrite(3, HIGH);
  pinMode(4, INPUT);
  digitalWrite(4, HIGH);
}

void loop() // run over and over
{
  int sensorValue1 = analogRead(1);
  int sensorValue2 = analogRead(2);
  int sensorValue3 = analogRead(3);
  mySerial.print(sensorValue1);
  mySerial.print(", ");
  mySerial.print(sensorValue2);
  mySerial.print(", ");
  mySerial.print(sensorValue3);
  mySerial.println();
} 


