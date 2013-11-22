void capSensing(){

  // sensing on pin 1:
  int n1 = chargeTime(PB1);
  if (n1 > calibration1) mySerial.print("1");
  else mySerial.print("0");
  previous1 = n1;
  delayMicroseconds(500);
  mySerial.print(","); // spacer

  // sensing on pin 2:
  int n2 = chargeTime(PB2);
  if (n2 > calibration2) mySerial.print("2");
  else mySerial.print("0");
  previous2 = n2;
  delayMicroseconds(500);
  mySerial.print(","); // spacer

  // sensing on pin 3:
  int n3 = chargeTime(PB3);
  if (n3 > calibration3) mySerial.print("3");
  else mySerial.print("0");
  previous3 = n3;
  delayMicroseconds(500);
  mySerial.print(","); // spacer

  // sensing on pin 4:
  int n4 = chargeTime(PB4);
  if (n4 > calibration4) mySerial.println("4");
  else mySerial.println("0");
  previous4 = n4;
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


