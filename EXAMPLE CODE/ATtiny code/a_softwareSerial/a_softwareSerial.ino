// software serial example for ATtiny!

#include <SoftwareSerial.h>

SoftwareSerial mySerial(0, 1); // RX, TX

void setup()  
{
  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);
  mySerial.println("Hello, world?");
  pinMode(4, INPUT_PULLUP);
}

void loop() // run over and over
{
   int sensorValue = analogRead(2);
    mySerial.println(sensorValue);
}
