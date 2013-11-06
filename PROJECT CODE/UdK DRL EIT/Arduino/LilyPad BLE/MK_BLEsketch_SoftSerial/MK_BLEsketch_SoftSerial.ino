#include <SoftwareSerial.h>

SoftwareSerial bleShield(2, 3);

long previousMillis = 0;
long interval = 1000; 

void setup()
{
  // set the data rate for the SoftwareSerial port
  bleShield.begin(19200);
  Serial.begin(19200);
}

void loop() // run over and over
{

  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;   
    
    //bleShield.write("hello");
//    bleShield.write(0x4D);
//    bleShield.write(0x2A);
//    bleShield.write(0x10);
//    bleShield.write(0x20);
  }

  if (bleShield.available()) {
    Serial.write(bleShield.read());
  }
  
  if (Serial.available()) {
    bleShield.write(Serial.read());
  }
}
