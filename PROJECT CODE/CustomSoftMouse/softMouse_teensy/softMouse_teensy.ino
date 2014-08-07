// Soft Mouse Interface

////////////////////////////////////////////////////////
// declare sensor input pins on Teensy: //
int sensorLeftClick = 0;
int sensorRIghtClick = 1;
int sensorMouseUp = 2;
int sensorMouseLeft = 3;
int sensorMouseDown = 4;
int sensorMouseRight = 5;
int sensorPins[] = { 
  0,1,2,3,4,5 }; 

// declare LED output pins on Teensy: //
int LEDpinCallibration = 0; // LED colour = yellow
int LEDpinLeftClick = 4; // LED colour = blue
int LEDpinRightClick = 3; // LED colour = pink
int LEDpinMouseUp = 6; // LED colour = white
int LEDpinMouseLeft = 8; // LED colour = white
int LEDpinMouseDown = 9; // LED colour = white
int LEDpinMouseRight = 10; // LED colour = white
int LEDpins[] = { 
  0,4,3,6,8,9,10 }; 

// declare variables for storing sensor values: //
int leftClick = 0;
int rightClick = 0;
int up = 0;
int left = 0;
int down = 0;
int right = 0;
int incomingValues[6];

////////////////////////////////////////////////////////
// SETUP //
void setup() {

  // define input pins: //
  for (int i = 0; i < 6 ; i++) {
    pinMode(sensorPins[i], INPUT);
    digitalWrite(sensorPins[i], HIGH); // use internal pull-up resistors:
  }

  // define output pins: //
  for (int i = 0; i < 7 ; i++) {
    pinMode(LEDpins[i], OUTPUT);
    digitalWrite(LEDpins[i], LOW); // turn all LEDs off
  }

  Serial.begin(9600); //begin serial communication at 9600 bauderate
}

////////////////////////////////////////////////////////
// LOOP //
void loop() {
testLEDs();
}

void testSENSORS() {
  for (int i = 0; i < 6 ; i++) {
    incomingValues[i] = analogRead(sensorPins[i]);
    Serial.print(incomingValues[i]);
    Serial.print(' ');
  }
  delay(100);
  Serial.println();

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

