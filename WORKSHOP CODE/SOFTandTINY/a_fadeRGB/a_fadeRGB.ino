// code for ATtiny
// fades an RGB LED through diferent colours

#define redPin 1
#define greenPin 0
#define bluePin 2
#define fadeTime 10

void setup(){
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}
void loop(){
  controlledFade(255,0,0, 0,255,0); //red to green
  controlledFade(0,255,0, 0,0,255); //green to blue
  controlledFade(0,0,255, 255,0,0); // blue to red
}
  void softPWM(int pin, int freq, int sp) {  // software PWM function that fakes analog output
    digitalWrite(pin,HIGH);  //on
    delayMicroseconds(sp*freq);
    digitalWrite(pin,LOW);  //off
    delayMicroseconds(sp*(255-freq));
  }
void controlledFade(int red1,int green1,int blue1, int red2,int green2,int blue2){
  float redDifference = 255.0 / (red1 - red2);
  float greenDifference = 255.0 / (green1 - green2);
  float blueDifference = 255.0 / (blue1 - blue2);
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue++) {
    float rValue = red1 - fadeValue/redDifference;
    float gValue = green1 - fadeValue/greenDifference;
    float bValue = blue1 - fadeValue/blueDifference;
    softPWM(redPin, rValue, 0);
    softPWM(greenPin, gValue, 0);
    softPWM(bluePin, bValue, 0);
    delay(fadeTime);
  }
}


