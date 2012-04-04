// RGB fade code for at tiny

int fadeTime = 10; // number of milli-seconds between colour fading

int rLEDPin = 5; // PWM
int gLEDPin = 3; // PWM
int bLEDPin = 6; // PWM
int outputs[] = {
  3,5,6};


float rValue, gValue, bValue;
float redDifference, blueDifference, greenDifference;






void setup() {
  for(int i = 0; i < 5; i++){
    pinMode(outputs[i],OUTPUT);
  }
}




void loop() {
  for(int i = 0; i < 1; i++){
    fadeTime = 10;
    fadeRGB();
  }

  off();
  delay(1000);

  for(int i = 0; i < 5; i++){
    fadeTime = 10;
    fadeRED();
  }

  off();
  delay(1000);
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




