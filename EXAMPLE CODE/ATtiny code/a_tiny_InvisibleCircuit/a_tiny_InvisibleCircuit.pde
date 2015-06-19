//                        attiny85
//                   reset -+---+- power
// (on while touching) pb3 -+*  +- pb2 (toggled by touch)
//       (touch input) pb4 -+   +- pb1 (fading while touching)
//                  ground -+---+- pb0 (fading always)


int togglepin = 1; // the led that's toggled when you touch the input pin

int calibration = 0;
int previous;

int randomval = 0;
int fadeval = 0, fadestep = 1;
int togglestate = LOW;

void setup()
{
  pinMode(togglepin, OUTPUT);
  
  delay(100);
  for (int i = 0; i < 8; i++) {
    calibration += chargeTime(PB3);
    delay(20);
  }
  calibration = (calibration + 4) / 8;
}

void loop()
{
  int n = chargeTime(PB3);
  
  
  if (previous <= calibration && n > calibration) {
    if (togglestate == LOW) togglestate = HIGH;
    else togglestate = LOW;
    
    digitalWrite(togglepin, togglestate);
  }
  
  previous = n;
  
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

