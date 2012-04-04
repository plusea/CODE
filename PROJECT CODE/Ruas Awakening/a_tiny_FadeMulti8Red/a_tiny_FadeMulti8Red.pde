//                        attiny85
//                   reset -+---+- power
// (on while touching) pb3 -+*  +- pb2 (toggled by touch)
//       (touch input) pb4 -+   +- pb1 (fading while touching)
//                  ground -+---+- pb0 (fading always)

int controlPinA = 3;
int controlPinB = 2;
int controlPinC = 4;
int r0 = 0;
int r1 = 0;
int r2 = 0;
int fadepin = 0; // the led that fades on and off
int fadepin0 = 1; // the led that fades on and off
int fadeValue1;
int fadeValue2;
int fadeValue3;

int calibration = 0;

int fadeval = 0, fadestep = 1;



void setup() {
  pinMode(fadepin, OUTPUT);
  pinMode(controlPinA, OUTPUT);
  pinMode(controlPinB, OUTPUT);
  pinMode(controlPinC, OUTPUT);

  delay(100);
  for (int i = 0; i < 8; i++) {
    calibration += chargeTime(PB4);
    delay(20);
  }
  calibration = (calibration + 4) / 8;
}



void loop() {
  int n = chargeTime(PB4);

  //  if (n > calibration) {

 for (int count=0; count<=7; count++) {
    r0 = bitRead(count,0);    // use this with arduino 0013 (and newer versions)    
    r1 = bitRead(count,1);    // use this with arduino 0013 (and newer versions)    
    r2 = bitRead(count,2);    // use this with arduino 0013 (and newer versions)    
    digitalWrite(controlPinA, r0);
    digitalWrite(controlPinB, r1);
    digitalWrite(controlPinC, r2);
    delay(1);
    if(count%2 == 0) analogWrite(fadepin, fadeval);
    else analogWrite(fadepin, 255-fadeval);
      } 

 



  //  }



  fadeval = fadeval + fadestep;
  if (fadeval == 254) fadestep = -1;
  if (fadeval == 1) fadestep = 1;
  //delayMicroseconds(500);
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






