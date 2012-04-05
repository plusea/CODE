//
// hannah perner-wilson, march 2011
// www.kit-of-no-parts.at
//
// code for sound and thermochromic output on an ATtiny85
// using leah buechley's sound code, taken from: http://web.media.mit.edu/~leah/LilyPad/07_sound_code.html
// and with much help and advice from david mellis
// !!! the clock speed fuse has been changed to be 8 times as fast as normal !!
//

int frequencyInHertz[] = {
  2093, 2349, 2637, 2793, 3136, 3520, 3951, 4186};  // array for note frequencies
long delayAmount;
long soundTimeSample;
long lastSample;
int BUTTONstate = 0;
int SENSORstate = 0;
int previousSENSORstate = 0;
int SENSORgo = 0;
int sensorPin = 2;
int speakerPin = 3;
int LED0 = 0;
int LED1 = 1;
int LED2 = 2;
int reading;
int count = 0;
int threshold = 850;

void setup()
{
  pinMode(sensorPin, INPUT);
  digitalWrite(4, HIGH);  // set internal pull-up resistor for sensorPin
  pinMode(speakerPin, OUTPUT);
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED0, HIGH);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
}

void loop() {

  if(millis() - lastSample > 50){ // only do everything (except modulate note frequency) every 20ms. this is to improve sound qualit
    lastSample= millis();
    reading = analogRead(sensorPin);

    // THERMOCHROMIC
    if(reading < threshold && BUTTONstate == 0){
      count++;
      BUTTONstate=1;
    }
    if(count == 1 && BUTTONstate == 1) {
      digitalWrite(LED0, HIGH);
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
    }
    if(count == 2  && BUTTONstate == 1) {
      digitalWrite(LED0, LOW);
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
    }
    if(count == 3  && BUTTONstate == 1) {
      digitalWrite(LED0, LOW);
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
    }
    if(count == 4  && BUTTONstate == 1) {
      digitalWrite(LED0, HIGH);
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
    }
    if(count > 4) count = 1;
    if(reading > threshold) BUTTONstate = 0;  

    // SOUND
    SENSORstate = reading/(threshold/8);
    if(SENSORstate != previousSENSORstate && SENSORstate < 8 && SENSORgo == 0){
      SENSORgo = 1;
      delayAmount = (long)(1000000/frequencyInHertz[SENSORstate]);
      soundTimeSample = millis();
    }
    if(millis()-soundTimeSample > 500){
      SENSORgo = 0;
    }
    previousSENSORstate = SENSORstate;
  }

  if(SENSORgo){  // play sound
    digitalWrite(speakerPin,HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(speakerPin,LOW);
    delayMicroseconds(delayAmount);
  }
}
