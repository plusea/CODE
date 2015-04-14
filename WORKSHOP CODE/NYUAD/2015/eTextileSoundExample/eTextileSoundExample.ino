// superLab(2015)
// sound code for etextiles sensor examples

//////// LilyPad USB ////////

// speaker connected to pin 11

// pressure, bend or stretch sensor can connect to:
// analog pins A2, A3, A4 or A5

// tilt sensor can connect to:
// digital pins 2, 3, 9 or 10

////////////////////////////////

// declare variables:
#define speakerPin 11
#define analogPin1 A3
#define analogPin2 A5
#define digitalPin1 2
#define digitalPin2 3
#define digitalPin3 9

int analogValue1 = 0;
int previousAnalogValue1 = 0;
int analogThreshold1 = 950;  //if sensor values passes this threshold then tone/melody/sound is triggered

int analogValue2 = 0;

int digitalValue1 = 0;
int digitalValue2 = 0;
int digitalValue3 = 0;



void setup() {
  pinMode(speakerPin, OUTPUT);  
  pinMode(analogPin1, INPUT_PULLUP); // turns on internal pull-up resistor, voltage divider (roughly 10K Ohm)
  pinMode(analogPin2, INPUT_PULLUP);
  pinMode(digitalPin1, INPUT_PULLUP);
  pinMode(digitalPin2, INPUT_PULLUP);
  pinMode(digitalPin3, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  analogValue1 = analogRead(analogPin1);
  analogValue2 = analogRead(analogPin2);
  digitalValue1 = analogRead(digitalPin1);
  digitalValue2 = analogRead(digitalPin2);
  digitalValue3 = analogRead(digitalPin3);

  // print all values 4 times a second:
  if(millis() % 250 == 0) {
    Serial.print("A1:");
    Serial.print(analogValue1);
    Serial.print("\t");
    Serial.print("A2:");
    Serial.print(analogValue2);
    Serial.print("\t");
    Serial.print("D1:");
    Serial.print(digitalValue1);
    Serial.print("\t");
    Serial.print("D2:");
    Serial.print(digitalValue2);
    Serial.print("\t");
    Serial.print("D3:");
    Serial.print(digitalValue3);
    Serial.println();
  }

  playPiano();
  //makeBeepSound();
  //makeNoiseSound();
  //playMelody();
}

//--------------------------------------------------------------------------------
// makes a beep sound for one second:
void makeBeepSound() {
  if(analogValue1 < analogThreshold1) tone(speakerPin, 1000, 1000);
}

//--------------------------------------------------------------------------------
void makeNoiseSound() {
  if(analogValue1 < analogThreshold1) tone(speakerPin, (1023-analogValue1)*4);
}

//--------------------------------------------------------------------------------
// PLAY PIANO //
// only play if sensor values is bellow set threshold
// divide the full range of the sensor into 8 segments
// depending in which segment the sensor values is currently in play a different note
// only play the note once per segment
void playPiano() {
  if(analogValue1 < analogThreshold1) {
    int sensorRange = 1023 - analogThreshold1;
    int toneRange = sensorRange/8;  // divides range of sensor into 8 segments
    if(analogValue1 != previousAnalogValue1) {
      previousAnalogValue1 = analogValue1;
      if(analogValue1 > 0 && analogValue1 < toneRange*1) tone(speakerPin, 2093, 500);
      if(analogValue1 > toneRange*1 && analogValue1 < toneRange*2) tone(speakerPin, 2349, 500);
      if(analogValue1 > toneRange*2 && analogValue1 < toneRange*3) tone(speakerPin, 2637, 500);
      if(analogValue1 > toneRange*3 && analogValue1 < toneRange*4) tone(speakerPin, 2793, 500);
      if(analogValue1 > toneRange*4 && analogValue1 < toneRange*5) tone(speakerPin, 3136, 500);
      if(analogValue1 > toneRange*5 && analogValue1 < toneRange*6) tone(speakerPin, 3520, 500);
      if(analogValue1 > toneRange*6 && analogValue1 < toneRange*7) tone(speakerPin, 3951, 500);
      if(analogValue1 > toneRange*7) tone(speakerPin, 4186, 500);
    }
  }
}

//--------------------------------------------------------------------------------
void bendPiano() {
  if(analogValue1 < 100 && analogValue1 > 90) tone(speakerPin, 2093);
  if(analogValue1 < 90 && analogValue1 > 80) tone(speakerPin, 2349);
  if(analogValue1 < 80 && analogValue1 > 70) tone(speakerPin, 2637);
  if(analogValue1 < 70 && analogValue1 > 60) tone(speakerPin, 2793);
  if(analogValue1 < 60 && analogValue1 > 50) tone(speakerPin, 3136);
  if(analogValue1 < 50 && analogValue1 > 40) tone(speakerPin, 3520);
  if(analogValue1 < 40 && analogValue1 > 30) tone(speakerPin, 3951);
  if(analogValue1 < 30 && analogValue1 > 20) tone(speakerPin, 4186);
  if(analogValue1 < 20) tone(speakerPin, 2093);
}

