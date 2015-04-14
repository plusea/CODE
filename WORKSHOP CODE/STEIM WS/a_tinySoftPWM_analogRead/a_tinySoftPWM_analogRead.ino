/*Software PWM on Attiny85
 Ernst Christensen 16.okt. 2011
 */

#define LED_fade 0
#define LED_brightness 1
#define sensorPin 3
int sensorValue = 0;
int count = 0;
int countDir = 1;

int fadeSpeed=5;


void setup(){
  pinMode(LED_fade,OUTPUT);
  pinMode(LED_brightness,OUTPUT);
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);
}


void loop(){
  sensorValue = analogRead(sensorPin);
  sensorValue = map(sensorValue, 0, 1023, 0, 255);

  // LED 0:    
  analogWrite(0,count);
  delay(sensorValue/10);
  count += countDir;
  if(count > 254) countDir = -1;
  if(count < 0) countDir = 1;

  // LED 1:
  analogWrite(1, sensorValue);
}


void spwm(int freq,int spin,int sp){

  //on
  digitalWrite(spin,HIGH);
  delayMicroseconds(sp*freq);

  // off
  digitalWrite(spin,LOW);
  delayMicroseconds(sp*(255-freq));


} //spwm









