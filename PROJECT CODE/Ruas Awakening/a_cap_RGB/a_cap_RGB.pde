// RGB fade code for at tiny

int fadeTime = 0; // number of milli-seconds between colour fading

int rLEDPin = 1; // PWM
int gLEDPin = 0; // PWM
int bLEDPin = 2;
int outputs[] = {
  0,1,2};
int sensorPin = 4;
int sensorValue;
float rValue, gValue, bValue;
float redDifference, blueDifference, greenDifference;

int calibration = 0;
int previous;

int randomval = 0;
int fadeval = 0, fadestep = 1;
int togglestate = LOW;






void setup() {
  for(int i = 0; i < 5; i++){
    pinMode(outputs[i],OUTPUT);
  }

  delay(100);
  for (int i = 0; i < 8; i++) {
    calibration += chargeTime(PB4);
    delay(20);
  }
  calibration = (calibration + 4) / 8;
}





void loop() {
  touchSensing();
  off();
  //testFade();
  //fadeRED();
  //fadeRGB();
}


void touchSensing(){
  int n = chargeTime(PB4);
  if (n > calibration){
    red();
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


void testFade(){
  controlledFade(0,0,0, 255,0,0);
  controlledFade(255,0,0, 0,0,0);
  controlledFade(0,0,0, 0,255,0);
  controlledFade(0,255,0, 0,0,0);
  controlledFade(0,0,0, 0,0,255);
  controlledFade(0,0,255, 0,0,0);
}

void fadeRED(){
  controlledFade(0,0,0, 100,100,100); //black to light white
  controlledFade(100,100,100, 255,197,3); //light white to yellow
  controlledFade(255,197,3, 255,87,3); //yellow to orange
  controlledFade(255,87,3, 0,0,0); //yellow to black

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
}

void fadeRGB(){
  controlledFade(255,0,0, 0,255,0); //red to green
  controlledFade(0,255,0, 0,0,255); //green to blue
  controlledFade(0,0,255, 255,0,0); // blue to red
}

void red(){
  analogWrite(rLEDPin, 255);
  analogWrite(gLEDPin, 0);
  analogWrite(bLEDPin, 0);
}

void off(){
  analogWrite(rLEDPin, 0);
  analogWrite(gLEDPin, 0);
  analogWrite(bLEDPin, 0);
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

