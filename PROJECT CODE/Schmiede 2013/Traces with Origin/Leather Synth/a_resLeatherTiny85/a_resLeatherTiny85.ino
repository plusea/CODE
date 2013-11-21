// software serial example for ATtiny!

#include <SoftwareSerial.h>

SoftwareSerial mySerial(5, 1); // RX, TX
int resPin1 = 0;
int resValue1;
int resPin2 = 2;
int resValue2;
int resPin3 = 3;
int resValue3;
int GNDpin = 0;


void setup()
{
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("starting...");
  pinMode(GNDpin, OUTPUT);
  digitalWrite(GNDpin, LOW);

  pinMode(2, INPUT);
  digitalWrite(2, HIGH);  //internal pullup
  pinMode(3, INPUT);
  digitalWrite(3, HIGH);  //internal pullup
  pinMode(0, INPUT);
  digitalWrite(0, HIGH);  //internal pullup
  
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);

}

void loop() // run over and over
{
  resValue1 = analogRead(resPin1);
  resValue2 = analogRead(resPin2);
  resValue3 = analogRead(resPin3);
  mySerial.print(resValue1);
  mySerial.print(", ");
  mySerial.print(resValue2);
  mySerial.print(", ");
  mySerial.print(resValue3);
  mySerial.println();
  delay(10);
} 








