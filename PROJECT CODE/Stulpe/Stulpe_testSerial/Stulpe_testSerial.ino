// code for hahnentritt stulpe by hannah
// runs on attiny45
// tests softserial

//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(0,1); // RX, TX

#include <SendOnlySoftwareSerial.h>
SendOnlySoftwareSerial mySerial (1);  // Tx pin 


void setup() {
  // set the data rate for the SoftwareSerial port
  mySerial.begin(57600);
  mySerial.println("starting...");  
}


void loop() {
  mySerial.println("hello");
  delay(100);
}
