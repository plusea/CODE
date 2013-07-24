// software serial example for ATtiny!

#include <SoftwareSerial.h>

SoftwareSerial mySerial(1, 0); // RX, TX
int inByte;
void setup()
{
  // set the data rate for the SoftwareSerial port
  mySerial.begin(57600);
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
  if (mySerial.available())
    inByte = mySerial.read();

  if(inByte == 'a'){
    mySerial.println("Mode A");
    pinMode(3, OUTPUT);
    digitalWrite(3, HIGH);
    delay(200);
    digitalWrite(3, LOW);
    delay(200);
  }  
  else{
    pinMode(3, INPUT);
    digitalWrite(3, HIGH);
  int sensorValue1 = analogRead(1);
  int sensorValue2 = analogRead(2);
  int sensorValue3 = analogRead(3);
  mySerial.print(sensorValue1);
  mySerial.print(",");
  mySerial.print(sensorValue2);
  mySerial.print(",");
  mySerial.print(sensorValue3);
  mySerial.println();
  }
  
  delay(10);
} 


