// software serial example for ATtiny!

#include <SoftwareSerial.h>

SoftwareSerial mySerial(5, 0); // RX, TX

int resPin1 = 2;
int resPin2 = 3;
int resPin3 = 4;

int resValue1;
int resValue2;
int resValue3;


void setup()
{
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("starting...");

  pinMode(2, INPUT);
  digitalWrite(2, HIGH);  //internal pullup
  pinMode(3, INPUT);
  digitalWrite(3, HIGH);  //internal pullup
  pinMode(4, INPUT);
  digitalWrite(4, HIGH);  //internal pullup
}

void loop() // run over and over
{
  resValue1 = analogRead(1);
  resValue3 = analogRead(3);
  resValue2 = analogRead(2);

  mySerial.print(resValue1);
  mySerial.print(", ");
  mySerial.print(resValue2);
  mySerial.print(", ");
  mySerial.print(resValue3);
  mySerial.println();
  delay(10);
} 








