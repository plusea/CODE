// MEMORY MOUNDS //
// capacitive sensing code running on ATtiny
// taken from Dave Mellis' "Touch" example code
// >> www. etextile-summercamp.org/swatch-exchange/memory-mounds/ 

#include <SendOnlySoftwareSerial.h>
SendOnlySoftwareSerial mySerial (1);  // Tx pin +

int calibration3 = 3;
int previous3;
int ledPin = 0;
int togglestate3 = LOW;

void setup() {
  // set the data rate for the SoftwareSerial port
  mySerial.begin(57600);
  mySerial.println("starting...");
  pinMode(ledPin, OUTPUT);
  // CAPACITIVE CALLIBRATION:
  delay(100);
  for (int i = 0; i < 8; i++) {
    calibration3 += chargeTime(PB3);
    delay(20);
  }
  calibration3 = (calibration3 + 4) / 8;
}

void loop() {
  int n3 = chargeTime(PB3);
  if (previous3 <= calibration3 && n3 > calibration3) {
    if (togglestate3 == LOW) togglestate3 = HIGH;
    else togglestate3 = LOW;
    digitalWrite(ledPin, togglestate3);
  }
  previous3 = n3;
  delayMicroseconds(500);
} 

byte chargeTime(byte pin) {
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
