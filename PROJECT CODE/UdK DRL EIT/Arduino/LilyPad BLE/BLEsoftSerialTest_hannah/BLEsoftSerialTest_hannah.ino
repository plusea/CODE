/*
  Software and Hardware serial to debug LilyPad BLE
 */

#include <SoftwareSerial.h>

SoftwareSerial BLEsoftSerial(2,3);
//SoftwareSerial portTwo(8,9);
char inByte = 'start';
void setup()
{

  Serial.begin(19200);
  BLEsoftSerial.begin(19200);

  pinMode(5, INPUT_PULLUP);
  pinMode(13, OUTPUT);
}

void loop()
{
  //BLEsoftSerial.listen();
  while (BLEsoftSerial.available() > 0) {
    inByte = BLEsoftSerial.read();

    if(inByte == 'n'){
      digitalWrite(13, HIGH);
      BLEsoftSerial.println("light ON");
    }

    else if(inByte == 'f')  {
      digitalWrite(13, LOW);
      BLEsoftSerial.println("light OFF");
    }

    else {
      Serial.println(inByte);  
      BLEsoftSerial.write(inByte);
    }


  }

  if(digitalRead(5) == LOW){
    Serial.println(inByte);
    BLEsoftSerial.write("contactTest");
  }





}










