/*
void capSensing(){
  //mySerial.println("Loop C");
  // sensing on pin 4:
  int n4 = chargeTime(PB4);
  if (n4 > calibration4) mySerial.print("4");
  else mySerial.print("0");
  previous4 = n4;
  delayMicroseconds(500);
  mySerial.print(","); // spacer
  // sensing on pin 3:
  int n3 = chargeTime(PB3);
  if (n3 > calibration3) mySerial.println("3");
  else mySerial.println("0");
  previous3 = n3;
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

*/
