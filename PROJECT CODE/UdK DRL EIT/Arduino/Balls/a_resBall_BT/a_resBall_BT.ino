// software serial example for ATtiny!

#include <SoftwareSerial.h>

SoftwareSerial mySerial(PA6, PA5); // RX, TX

void setup()
{
  pinMode(PA0, INPUT); 
  digitalWrite(PA0, HIGH);
  pinMode(PA1, INPUT); 
  digitalWrite(PA1, HIGH);
  pinMode(PA2, INPUT); 
  digitalWrite(PA2, HIGH);
  pinMode(PA3, INPUT); 
  digitalWrite(PA3, HIGH);
  pinMode(PA4, INPUT); 
  digitalWrite(PA4, HIGH);
  pinMode(PA7, INPUT); 
  digitalWrite(PA7, HIGH);
  mySerial.begin(57600);
  mySerial.println("starting...");
}

void loop() // run over and over
{
  mySerial.print(analogRead(0));
  mySerial.print(",");
  mySerial.print(analogRead(1));
  mySerial.print(",");
  mySerial.print(analogRead(2));
  mySerial.print(",");
  mySerial.print(analogRead(3));
  mySerial.print(",");
  mySerial.print(analogRead(4));
  mySerial.print(",");
  mySerial.print(analogRead(7));
  mySerial.println();
  delay(100);
} 





