// cap sensing and software serial example for ATtiny!
// taken from Dave Mellis' Touch example code

#include <SendOnlySoftwareSerial.h>
SendOnlySoftwareSerial mySerial (1);  // Tx pin 

int calibration3 = 3;
int previous3;
int ledPin = 0;
int togglestate3 = LOW;
int memory1;
int memory2;
int memory3;
boolean on = false;
int startON;
int endON;
int durationON;
int waitTime = 5000;
int timer;

void setup()
{
  // set the data rate for the SoftwareSerial port
  mySerial.begin(57600);
  mySerial.println("starting...");

  pinMode(ledPin, OUTPUT);

  // CAPACITIVE CALLIBRATION
  // calibrate pin 1:
  delay(100);
  for (int i = 0; i < 8; i++) {
    calibration3 += chargeTime(PB3);
    delay(20);
  }
  calibration3 = (calibration3 + 4) / 8;
}


void loop()
{
  int n3 = chargeTime(PB3);
  // TOGGLE CODE:
  if (previous3 <= calibration3 && n3 > calibration3) {
    if (togglestate3 == LOW) togglestate3 = HIGH;
    else togglestate3 = LOW;
    digitalWrite(ledPin, togglestate3);
  }
  previous3 = n3;


  // MEMORY CODE:
  if (n3 > calibration3 && on == false){
    on = true;
    digitalWrite(ledPin, HIGH);
    startON = millis();
    timer = millis();
  }
  if (n3 < calibration3 && on == true){
    on = false;
    digitalWrite(ledPin, LOW);
    endON = millis();
    durationON = endON - startON;
    timer = millis();
  }  

  // repeat
  if (n3 < calibration3 && millis()-timer > waitTime){
    n3 = chargeTime(PB3);
    digitalWrite(ledPin, HIGH);
    delay(durationON);
    digitalWrite(ledPin, LOW);
    delay(durationON);
  }

  delayMicroseconds(500);
} 


byte chargeTime(byte pin)
{
  byte mask = (1 << pin);
  byte i;

  DDRB &= ~mask; // input
  PORTB |= mask; // pull-up on

  for (i = 0; i < 16; i++) {
    if (PINB & mask) break;
  }

  PORTB &= ~mask; // pull-up off
  DDRB |= mask; // discharge

  return i;
}











