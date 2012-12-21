 #include "pitches.h"

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

// COM
int WiFlyPin1 = 10;
int WiFlyPin2 = 11;
int WiFlyPin3 = 12;
int WiFlyPin4 = 13;

// INCOMING VALUES
int rBend, lBend, squeeze, tilt1, tilt2, x, y, z;
int rightBendAmount, leftBendAmount, squeezeAmount, tiltDirection;
byte inByte;

// THRESHOLDS
int rBendMax = 500;
int rBendMin = 100;
int lBendMax = 500;
int lBendMin = 100;
int squeezeMax = 160;
int squeezeMin = 100;



// notes in the melody:
int melody[] = {NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };

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

  //Serial.begin(9600);
  Serial.begin(115200);
  //establishContact();  // send a byte to establish contact until receiver responds 
  noTone(speakerPin);
}

void loop() {

  // OUTPUT //

  // read input pins and assign incoming values to variables
  rBend = analogRead(rBendPin);
  lBend = analogRead(lBendPin);
  squeeze = analogRead(squeezePin);
  x = analogRead(xPin);
  y = analogRead(yPin);
  z = analogRead(zPin);
  tilt1 = digitalRead(tilt1Pin);
  tilt2 = digitalRead(tilt2Pin);

  // TILT DIRECTION // 
  if(tilt1 == 1 && tilt2 == 1) {
    tiltDirection = 1;
  }
  if(tilt1 == 0 && tilt2 == 0) {
    tiltDirection = 2;
  }
  if(tilt1 == 1 && tilt2 == 0) {
    tiltDirection = 3;
  } 
  if(tilt1 == 0 && tilt2 == 1) {
    tiltDirection = 4;
  }
  
  // RIGHT WING  // 
  if(rBend < 400 && rBend > 300) rightBendAmount = 1;
  else if(rBend < 300 && rBend > 100) rightBendAmount = 2;
  else if(rBend < 100) rightBendAmount = 3;
  else rightBendAmount = 0;
  
  // LEFT WING  // 
  if(lBend < 400 && lBend > 300) leftBendAmount = 1;
  else if(lBend < 300 && lBend > 100) leftBendAmount = 2;
  else if(lBend < 100) leftBendAmount = 3;
  else leftBendAmount = 0;
  
  // SQUEEZE AMOUNT // 
  if(squeeze < 1000 && squeeze > 950) squeezeAmount = 1;
  else if(squeeze < 950 && squeeze > 900) squeezeAmount = 2;
  else if(squeeze < 900) squeezeAmount = 3;
  else squeezeAmount = 0;
  
  // print relevant variable values with comman inbetween each:
  // wing bend:
  Serial.print(rightBendAmount);
  Serial.print(",");
  Serial.print(leftBendAmount);
  // squeeze:
  Serial.print(",");
  Serial.print(squeezeAmount);
  // tilt direction:
  Serial.print(",");
  Serial.print(tiltDirection);
  // accelerometer:
  Serial.print(",");
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.print(z);

  //Serial.print(",");
  //Serial.print(inByte);
  Serial.println("");  // line break
  //Serial.print("\t");


  // INPUT //

  // read serial input
  if (Serial.available() > 0) {
    inByte = byte(Serial.read());  // get incoming byte
  }

  // LED LIGHT //  
  if(inByte == 'r') {  // LED red
    analogWrite(rLEDPin, 255);
    analogWrite(gLEDPin, 0);
    analogWrite(bLEDPin, 0);
  }
  else if(inByte == 'g') {  // LED green
    analogWrite(rLEDPin, 0);
    analogWrite(gLEDPin, 255);
    analogWrite(bLEDPin, 0);
  }
  else if(inByte == 'b') {  // LED blue
    analogWrite(rLEDPin, 0);
    analogWrite(gLEDPin, 0);
    analogWrite(bLEDPin, 255);
  }
  else if(inByte == 'w') {  // LED white
    analogWrite(rLEDPin, 255);
    analogWrite(gLEDPin, 255);
    analogWrite(bLEDPin, 255);
  }
  else if(inByte == 'z') {  // LED off
    analogWrite(rLEDPin, 0);
    analogWrite(gLEDPin, 0);
    analogWrite(bLEDPin, 0);
  }

  // SOUND //
  if(inByte == 'q') {  // quiet volume melody
    play(1);
  } 
  else if(inByte == 'm') {  //  moderate volume melody
    play(2);
  }
  else if(inByte == 'l') {  // loud volume melody
    play(3);
  }
  else if(inByte == 'n') {  // no melody
    noTone(speakerPin);
  }

  // VIBRATION //
  if(inByte == 't') { // timid vibration
    analogWrite(vibePin, 125);
  } 
  else if(inByte == 'v') {  // medium vibration
    analogWrite(vibePin, 200);
  }
  else if(inByte == 'h') {  // hard vibration
    analogWrite(vibePin, 255);
  }
  else if(inByte == 's') {  // vibration off
    analogWrite(vibePin, 0);
  }
  
  delay(10);
}



void play(int vol){
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

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('A', BYTE);   // send a capital A
    delay(300);
  }
}






