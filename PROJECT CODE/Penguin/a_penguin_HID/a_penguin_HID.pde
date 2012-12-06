// Penguin Interface code for sending keystrokes from arduino to computer via HID bluetooth module
// project page >> http://www.plusea.at/?page_id=2700

#include "pitches.h"

////////////////////////
// EDITABLE VARIABLES //
////////////////////////
int keyDelay = 500;  // number of milli-seconds between key presses when key pressed
int lightDelay = 1400;  // number of milli-seconds between LED light colours

int squeezeThreshold = 900; // sensor value needs to go bellow this value to trigger

int rightWingThresholdMIN = 200; // sensor value needs to go bellow this value to trigger
int rightWingThresholdMAX = 400; // sensor value needs to stay above this value not to trigger

int leftWingThresholdMIN = 200; // sensor value needs to go bellow this value to trigger
int leftWingThresholdMAX = 400; // sensor value needs to stay above this value not to trigger

//////////
// PINS //
//////////
// INPUTS
int rBendPin = A0;  // analog
int lBendPin = A1;  // analog
int squeezePin = A2;  // analog
int xPin = A3;  // analog
int yPin = A4;  // analog
int zPin = A5;  // analog
int tilt1Pin = 7;  // digital
int tilt2Pin = 8;  // digital
int strokePin;  // digital
int beakPin;  // digital
int inputs[] = {
  A0,A1,A2,A3,A4,A5,7,8};  //8
int pullups[] = {
  14,15,16,17,18,19,7,8};  //8

// OUTPUTS
int rLEDPin = 6; // PWM
int gLEDPin = 5; // PWM
int bLEDPin = 3; // PWM
int speakerPin = 4;
int vibePin = 9; // PWM
int outputs[] = {
  5,6,3,4,9};  //5

//////////
// WIFI //
//////////
int WiFlyPin1 = 10;
int WiFlyPin2 = 11;
int WiFlyPin3 = 12;
int WiFlyPin4 = 13;

////////////
// INPUTS //
////////////
// INCOMING VALUES
int rBend, lBend, squeeze, tilt1, tilt2, x, y, z;
int rightBendAmount, leftBendAmount, squeezeAmount, tiltDirection;
byte inByte;

///////////
// SOUND //
///////////
// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };

///////////
// LIGHT //
///////////
int rgb;  //for keeping track of LED light colour
int light;  //for keeping track ot LED colour change timing

//////////
// KEYS //
//////////
byte right = 0x07;
byte left = 0x0B;
byte up = 0x0E;
byte down = 0x0C;
byte enter = 0x0D;
int u,d,r,l,e;  //for keeping track of keyDelay time






///////////
// SETUP //
///////////
void setup() {
  for(int i = 0; i < 5; i++){
    pinMode(outputs[i],OUTPUT);
  }

  for(int i = 0; i < 8; i++){
    pinMode(inputs[i],INPUT);
  }

  for(int i = 0; i < 8; i++){
    digitalWrite(pullups[i],HIGH);
  }

  Serial.begin(115200);
  noTone(speakerPin);
}






//////////
// LOOP //
//////////
void loop() {

  // read input pins and assign incoming values to variables
  rBend = analogRead(rBendPin);
  lBend = analogRead(lBendPin);
  squeeze = analogRead(squeezePin);
  x = analogRead(xPin);
  y = analogRead(yPin);
  z = analogRead(zPin);
  tilt1 = digitalRead(tilt1Pin);
  tilt2 = digitalRead(tilt2Pin);

  // tilt upright --> neutral
  if(tilt1 == 0 && tilt2 == 0) {  // reset delay time variables
    u = 0;
    d = 0;
    r = 0;
    l = 0;
  }

  // tilt back --> down
  if(tilt1 == 1 && tilt2 == 1) {
    if(d == 0 || d % keyDelay == 0) {  // key pressed every keyDelay milli-seconds
      Serial.write(down);
      delay(25); // must delay 25 milli-seconds after each keypress!
    }
    d++;
  }

  // tilt right --> right
  if(tilt1 == 1 && tilt2 == 0) {
    if(r == 0 || r % keyDelay == 0) {
      Serial.write(right);
      delay(25); // must delay 25 milli-seconds after each keypress!
    }
    r++;
  } 

  // tilt left --> left
  if(tilt1 == 0 && tilt2 == 1) {
    if(l == 0 || l % keyDelay == 0) {
      Serial.write(left);
      delay(25); // must delay 25 milli-seconds after each keypress!
    }
    l++;
  }

  // squeeze or bend both wings --> up
  if(rBend < rightWingThresholdMIN && lBend << leftWingThresholdMIN) {
    if(u == 0 || u % keyDelay == 0) {
      Serial.write(up);
      delay(25); // must delay 25 milli-seconds after each keypress!
    }
    u++;
  }

  // Squeeze --> press enter key and vibrate
  if(squeeze < squeezeThreshold){
    analogWrite(vibePin, 255);
  }
  if(squeeze < squeezeThreshold && e == 1) {
    e = 0;  //key is only pressed once
    Serial.write(enter);
    delay(25); // must delay 25 milli-seconds after each keypress!
  }
  if(squeeze > squeezeThreshold) {
    e = 1;
    analogWrite(vibePin, 0);
  }

  // squeeze or bend right wing only --> toggle through LED colours
  if(rBend < rightWingThresholdMIN && lBend > leftWingThresholdMAX) {
    if(light == 0 || light % lightDelay == 0) {
      rgb++;
    }
    light++;
  }
  else {
    light = 0;
    rgb = 0;
    analogWrite(rLEDPin, 0);
    analogWrite(gLEDPin, 0);
    analogWrite(bLEDPin, 0);
  }

  // LED red
  if(rgb == 1) {
    analogWrite(rLEDPin, 255);
    analogWrite(gLEDPin, 0);
    analogWrite(bLEDPin, 0);
  }

  // LED red and green
  if(rgb == 2) {
    analogWrite(rLEDPin, 150);
    analogWrite(gLEDPin, 255);
    analogWrite(bLEDPin, 0);
  }

  // LED green
  if(rgb == 3) {
    analogWrite(rLEDPin, 0);
    analogWrite(gLEDPin, 255);
    analogWrite(bLEDPin, 0);
  }

  // LED green and blue
  if(rgb == 4) {
    analogWrite(rLEDPin, 0);
    analogWrite(gLEDPin, 255);
    analogWrite(bLEDPin, 255);
  }

  // LED blue
  if(rgb == 5) {
    analogWrite(rLEDPin, 0);
    analogWrite(gLEDPin, 0);
    analogWrite(bLEDPin, 255);
  }

  // LED blue and red
  if(rgb == 6) {
    analogWrite(rLEDPin, 150);
    analogWrite(gLEDPin, 0);
    analogWrite(bLEDPin, 255);
  }

  // LED white
  if(rgb == 7) {
    analogWrite(rLEDPin, 255);
    analogWrite(gLEDPin, 255);
    analogWrite(bLEDPin, 255);
  }

  if(rgb > 7) rgb = 0;



  // squeeze or bend left wing only --> play melody
  if(lBend < leftWingThresholdMIN && rBend > rightWingThresholdMAX) {
    play(1);
  }
  else noTone(speakerPin);








}







///////////
// SOUND //
///////////
void play(int vol) {
  int volume = vol;
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(speakerPin, volume*melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    inByte = 'n';
  }
}






