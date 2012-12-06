// Pillow Interface code for fading RGB leds between given colours
// and for sending keystrokes from arduino to computer via HID bluetooth module
// project page >> http://www.plusea.at/?page_id=3132

#include "pitches.h"

////////////////////////
// EDITABLE VARIABLES //
////////////////////////
int keyDelay = 500; // number of milli-seconds between key presses when key pressed

int fadeTime = 10; // number of milli-seconds between colour fading

int squeezeThreshold = 900; // sensor value needs to go bellow this value to trigger

//////////
// PINS //
//////////
// INPUTS
int squeezePin = A2; // analog
int tilt1Pin = 7; // digital
int tilt2Pin = 8; // digital
int inputs[] = {
  A2,7,8}; //3
int pullups[] = {
  16,7,8}; //3

// OUTPUTS
int rLEDPin = 3; // PWM
int gLEDPin = 6; // PWM
int bLEDPin = 5; // PWM
int speakerPin = 4;
int vibePin = 2; // PWM
int outputs[] = {
  2,3,6,5,4}; //5
  
////////////
// INPUTS //
////////////
// INCOMING VALUES
int squeeze, tilt1, tilt2;
int squeezeAmount, tiltDirection;
int inByte;

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
float rValue, gValue, bValue;
float redDifference, blueDifference, greenDifference;

//////////
// KEYS //
//////////
byte right = 0x07;
byte left = 0x0B;
byte up = 0x0E;
byte down = 0x0C;
byte enter = 0x0D;
int u,d,r,l,e; //for keeping track of keyDelay time


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
  
  digitalWrite(vibePin, HIGH);
}


//////////
// LOOP //
//////////
void loop() {

  controlledFade(150,255,0, 0,255,100); //orange to turquoise
  controlledFade(0,255,100, 0,50,255); //turquoise to dark blue
  controlledFade(0,50,255, 0,255,255); // dark blue to light blue
  controlledFade(0,255,255, 20,50,250); //light blue to purple
  controlledFade(20,50,250, 50,255,255); //purple to white
  controlledFade(50,255,255, 50,250,0); //white to yellow
  controlledFade(50,250,0, 100,0,250); //yellow to pink
  controlledFade(100,0,250, 150,255,0); //pink to orange
  
  //function "sensorKeys" is called within "controlledFade"!
 
}


/////////////////
// SENSOR KEYS //
/////////////////
void sensorKeys() {
   // read input pins and assign incoming values to variables
  squeeze = analogRead(squeezePin);
  tilt1 = digitalRead(tilt1Pin);
  tilt2 = digitalRead(tilt2Pin);

  // tilt upright --> neutral
  if(tilt1 == 0 && tilt2 == 0) { // reset delay time variables
    u = 0;
    d = 0;
    r = 0;
    l = 0;
  }

  // tilt back --> down
  if(tilt1 == 1 && tilt2 == 1) {
    if(d == 0 || d % keyDelay == 0) { // key pressed every keyDelay milli-seconds
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

  // Squeeze --> press enter key and vibrate
  if(squeeze < squeezeThreshold){
    digitalWrite(vibePin, HIGH);
  }
  if(squeeze < squeezeThreshold && e == 1) {
    e = 0; //key is only pressed once
    Serial.write(enter);
    delay(25); // must delay 25 milli-seconds after each keypress!
    play(1);
  }
  if(squeeze > squeezeThreshold) {
    e = 1;
    digitalWrite(vibePin, LOW);
  }
  
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


///////////
// LIGHT //
///////////
void controlledFade(int r1,int g1,int b1, int r2,int g2,int b2){
  int red1 = r1;
  int green1 = g1;
  int blue1 = b1;
  int red2 = r2;
  int green2 = g2;
  int blue2 = b2
  
  
  ;

  redDifference = 255.0 / (red1 - red2);
  greenDifference = 255.0 / (green1 - green2);
  blueDifference = 255.0 / (blue1 - blue2);

  /*
Serial.print("differences"); // for testing purposes print difference values
Serial.print(",");
Serial.print(redDifference);
Serial.print(",");
Serial.print(greenDifference);
Serial.print(",");
Serial.print(blueDifference);
Serial.println("");
*/
  
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue++) {
    rValue = red1 - fadeValue/redDifference;
    gValue = green1 - fadeValue/greenDifference;
    bValue = blue1 - fadeValue/blueDifference;
    
    analogWrite(rLEDPin, rValue);
    analogWrite(gLEDPin, gValue);
    analogWrite(bLEDPin, bValue);
    delay(fadeTime);
    
    sensorKeys();
  }
  
  /*
Serial.print("colour"); // for testing purposes print colour values
Serial.print(",");
Serial.print(rValue);
Serial.print(",");
Serial.print(gValue);
Serial.print(",");
Serial.print(bValue);
Serial.println("");
*/
}



