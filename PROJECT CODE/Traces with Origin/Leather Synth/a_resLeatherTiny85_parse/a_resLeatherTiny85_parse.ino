// software serial example for ATtiny!

// hmmmm......
// the input from two pins being touched will always be the same.....


#include <SoftwareSerial.h>

SoftwareSerial mySerial(5, 0); // RX, TX
int resPin1 = 1;
int resPin2 = 2;
int resPin3 = 3;
int resPin4 = 4;

int resValue1;
int resValue2;
int resValue3;
int resValue4;


void setup()
{
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("starting...");
}

void loop() // run over and over
{
  // READ RES PIN 1
  pinMode(1, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(1, HIGH);  //internal pullup
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  delay(1);
  resValue1 = digitalRead(1);
  delay(1);

  // READ RES PIN 2
  pinMode(1, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(1, LOW);
  digitalWrite(2, HIGH);  //internal pullup
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);

  delay(1);
  resValue2 = analogRead(1); // PB2 = ADC1
  delay(1);

  // READ RES PIN 3
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
  pinMode(4, OUTPUT);
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);  //internal pullup
  digitalWrite(4, LOW);
  delay(1);
  resValue3 = analogRead(3); // PB3 = ADC3
  delay(1);

  // READ RES PIN 4
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, INPUT);
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);  //internal pullup
  delay(1);
  resValue4 = analogRead(2); // PB4 = ADC2
  delay(1);

  mySerial.print(resValue1);
  mySerial.print(", ");
  mySerial.print(resValue2);
  mySerial.print(", ");
  mySerial.print(resValue3);
  mySerial.print(", ");
  mySerial.print(resValue4);
  mySerial.println();
  delay(1);
} 










