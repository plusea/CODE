// Soft Mouse Interface

////////////////////////////////////////////////////////
// declare sensor input pins on Teensy: //
int sensorLeftClick = 0;
int sensorRIghtClick = 1;
int sensorMouseUp = 2;
int sensorMouseLeft = 3;
int sensorMouseDown = 4;
int sensorMouseRight = 5;
byte sensorPins2[] = { 
  A6,A7,A8,A9,A10 }; 
byte sensorPins3[] = { 
  A0,A1,A2,A3,A4,A5 }; 
byte sensorPins[] = { 
  A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10 }; 

// declare LED output pins on Teensy: //
int LEDpinCallibration = 0; // LED colour = yellow
int LEDpinLeftClick = 4; // LED colour = blue
int LEDpinRightClick = 3; // LED colour = pink
int LEDpinMouseUp = 6; // LED colour = white
int LEDpinMouseLeft = 8; // LED colour = white
int LEDpinMouseDown = 9; // LED colour = white
int LEDpinMouseRight = 10; // LED colour = white
int LEDpins[] = { 
  0,4,3,6,8,7,5 }; 

// declare variables for storing sensor values: //
int leftClick = 0;
int rightClick = 0;
int up = 0;
int left = 0;
int down = 0;
int right = 0;
int incomingValues[11];

////////////////////////////////////////////////////////
// SETUP //
void setup() {
//  // define input pins: //
//  for (int i = 0; i < 6 ; i++) {
//    //pinMode(sensorPins2[i], INPUT_PULLUP); // use internal pull-up resistors
//    pinMode(sensorPins3[i], INPUT); // do NOT use internal pull-up resistors
//  }
//  for (int i = 0; i < 5 ; i++) {
//    pinMode(sensorPins2[i], INPUT_PULLUP); // use internal pull-up resistors
//    //pinMode(sensorPins[i], INPUT); // do NOT use internal pull-up resistors
//  }

pinMode(11, OUTPUT);
digitalWrite(11, LOW);
pinMode(A0, INPUT);
pinMode(A9, INPUT_PULLUP);

//  // define output pins: //
//  for (int i = 0; i < 7 ; i++) {
//    pinMode(LEDpins[i], OUTPUT);
//    digitalWrite(LEDpins[i], LOW); // turn all LEDs off
//  }

  Serial.begin(9600); //begin serial communication at 9600 bauderate
}

////////////////////////////////////////////////////////
// LOOP //
void loop() {
  testSENSORS();
  
}

void testSENSORS() {
//  for (int i = 0; i < 11 ; i++) {
//    incomingValues[i] = analogRead(sensorPins[i]);
//    Serial.print(incomingValues[i]);
//    Serial.print("\t");
//  }
int sensor0 = analogRead(A0);
int sensor9 = analogRead(A9);
Serial.print(sensor0);
Serial.print("\t");
Serial.print(sensor9);
Serial.println();
delay(100);
}

void testLEDs() {
  for (int i = 0; i < 7 ; i++) {
    digitalWrite(LEDpins[i], HIGH);
    delay(250);
    digitalWrite(LEDpins[i], LOW);
  }
}


void allLEDSon() {
  for (int i = 0; i < 7 ; i++) {
    digitalWrite(LEDpins[i], HIGH);
  }
}

void allLEDSoff() {
  for (int i = 0; i < 7 ; i++) {
    digitalWrite(LEDpins[i], LOW);
  }
}


