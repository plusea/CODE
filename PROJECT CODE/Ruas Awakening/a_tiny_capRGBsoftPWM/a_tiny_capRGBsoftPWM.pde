/*
code based on dave mellis's touch example
 >> 
 */

//                        attiny85
//                   reset -+---+- power
// (on while touching) pb3 -+*  +- pb2 (toggled by touch)
//       (touch input) pb4 -+   +- pb1 (fading while touching)
//                  ground -+---+- pb0 (fading always)



int rLEDPin = 1; // PWM
int gLEDPin = 0; // PWM
int bLEDPin = 2; // PWM
float rValue, gValue, bValue;
float redDifference, blueDifference, greenDifference;
int fadeTime = 5; // number of milli-seconds between colour fading

int calibration = 0;
int microDelay = 1000;

float fadeval = 0;
float fadestep = 0.01;

void setup()
{
  pinMode(rLEDPin, OUTPUT);
  pinMode(gLEDPin, OUTPUT);
  pinMode(bLEDPin, OUTPUT);

  delay(100);
  for (int i = 0; i < 8; i++) {
    calibration += chargeTime(PB4);
    delay(20);
  }
  calibration = (calibration + 4) / 8;
}






void loop() {
  int n = chargeTime(PB4);
  if (n > calibration) {
    fadeRED();
  }
}




void fadeRED(){
  controlledFade(0,0,0, 255,255,0); //black to light white
  controlledFade(255,255,0, 255,197,0); //light white to yellow
  controlledFade(255,197,0, 255,87,0); //yellow to orange
  controlledFade(255,87,0, 0,0,0); //yellow to black
    controlledFade(0,0,0, 255,255,0); //black to light white
  controlledFade(255,255,0, 255,197,0); //light white to yellow
  controlledFade(255,197,0, 255,87,0); //yellow to orange
  controlledFade(255,87,0, 0,0,0); //yellow to black

  controlledFade(0,0,0, 100,0,0); // black to light red
  controlledFade(100,0,0, 255,255,0); // light red to white
  controlledFade(255,255,0, 150,0,0); // black to light red
  controlledFade(150,0,0, 0,0,0); // light red to black
  controlledFade(0,0,0, 200,0,0); // black to light red
  controlledFade(200,0,0, 50,0,0); // light red to black


  controlledFade(0,0,0, 100,0,0); // black to light red
  controlledFade(100,0,0, 0,0,0); // light red to black
  controlledFade(0,0,0, 150,0,0); // black to light red
  controlledFade(150,0,0, 0,0,0); // light red to black
  controlledFade(0,0,0, 200,0,0); // black to light red
  controlledFade(200,0,0, 50,0,0); // light red to black

  controlledFade(50,0,0, 255,0,0); // black to red
  controlledFade(255,0,0, 50,0,0); // red to black
  controlledFade(50,0,0, 255,0,0); // black to red
  controlledFade(255,0,0, 100,0,0); // red to black
  controlledFade(100,0,0, 255,0,0); // black to red
  controlledFade(255,0,0, 0,0,0); // red to black
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





void spwm(int freq,int pin,int sp){

  //on
  digitalWrite(pin,HIGH);
  delayMicroseconds(sp*freq);

  // off
  digitalWrite(pin,LOW);
  delayMicroseconds(sp*(255-freq));
} //spwm







void controlledSoftFade(int r1,int g1,int b1, int r2,int g2,int b2){
  int red1 = r1;
  int green1 = g1;
  int blue1 = b1;
  int red2 = r2;
  int green2 = g2;
  int blue2 = b2;

  redDifference = 255.0 / (red1 - red2);
  greenDifference = 255.0 / (green1 - green2);
  blueDifference = 255.0 / (blue1 - blue2);

  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue++) {
    rValue = red1 - fadeValue/redDifference;
    gValue = green1 - fadeValue/greenDifference;
    bValue = blue1 - fadeValue/blueDifference;

    spwm(rValue,rLEDPin,20);
    spwm(gValue,gLEDPin,20);
    spwm(bValue,bLEDPin,20);
  }
}

void controlledFade(int r1,int g1,int b1, int r2,int g2,int b2){
  int red1 = r1;
  int green1 = g1;
  int blue1 = b1;
  int red2 = r2;
  int green2 = g2;
  int blue2 = b2;

  redDifference = 255.0 / (red1 - red2);
  greenDifference = 255.0 / (green1 - green2);
  blueDifference = 255.0 / (blue1 - blue2);


  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue++) {
    rValue = red1 - fadeValue/redDifference;
    gValue = green1 - fadeValue/greenDifference;
    bValue = blue1 - fadeValue/blueDifference;

    analogWrite(rLEDPin, rValue);
    analogWrite(gLEDPin, gValue);
    analogWrite(bLEDPin, bValue);
    delay(fadeTime);
  }
}


