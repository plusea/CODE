// code for ATtiny
// reads the analog value of a textile sensor (attach external pull-up resistor)
// mapps the value from the analog sensor to the colour spectrum of an RGB led

#define red 1
#define green 0
#define blue 2
#define sensor 2
int sensorValue =   0;

void setup(){
pinMode(red, OUTPUT);
pinMode(green, OUTPUT);
pinMode(blue, OUTPUT);
pinMode(3, INPUT);
}

void loop(){
sensorValue = analogRead(2);
if(sensorValue >= 0 && sensorValue < 255) spwm(red, sensorValue);
if(sensorValue >= 255 && sensorValue < 510) {
  spwm(red, 510-sensorValue);
  spwm(green, sensorValue-255);
  }
if(sensorValue >= 510 && sensorValue < 765) {
  spwm(green, 765-sensorValue);
  spwm(blue, sensorValue-510);
  }
}

// software PWM function that fakes analog output:
void spwm(int freq,int pin){
digitalWrite(pin,HIGH);  //on
delayMicroseconds(freq);
digitalWrite(pin,LOW);  //off
delayMicroseconds(freq);
}
