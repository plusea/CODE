// INPUTS
int RbendPin = A0;
int LbendPin = A1;
int squeezePin = A2;
int xPin = A5;
int yPin = A4;
int zPin = A3;

// OUTPUTS
int vibePin = 9; // PWM
int redLEDPin = 6; // PWM
int greenLEDPin = 5; // PWM
int blueLEDPin = 3; // PWM
int speakerPin = 4;
int tiltPin1 = 7;
int tiltPin2 = 8;

// Incoming sensor values:
int Rbend, Lbend, squeeze, tilt1, tilt2, x, y, z;

// Thresholds
int RbendMax = 500;
int RbendMin = 70;
int LbendMax = 500;
int LbendMin = 70;
int squeezeMax = 160;
int squeezeMin = 80;

// Incoming byte (from computer)
byte command;
String key = "direction...";


void setup() {
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(speakerPin, OUTPUT);
  pinMode(vibePin, OUTPUT);

  // set pullup resistors:
  digitalWrite(14,HIGH);  // bend sensor
  digitalWrite(15,HIGH);  // bend sensor
  digitalWrite(16,HIGH);  // squeeze sensor

  Serial.begin(9600);
  establishContact();  // send a byte to establish contact until receiver responds 

  noTone(speakerPin);
}

void loop() {

  if (Serial.available() > 0) {
    // get incoming byte:
    command = byte(Serial.read());
  }

  Lbend = analogRead(LbendPin);
  Rbend = analogRead(RbendPin);
  squeeze = analogRead(squeezePin);
  x = analogRead(xPin);
  y = analogRead(yPin);
  z = analogRead(zPin);
  tilt1 = digitalRead(tiltPin1);
  tilt2 = digitalRead(tiltPin2);

  /*
  Lbend = constrain(Lbend, LbendMin, LbendMax);
   Rbend = constrain(Rbend, RbendMin, RbendMax);
   squeeze = constrain(squeeze, squeezeMin, squeezeMax);
   Lbend = map(Lbend, LbendMin, LbendMax, 0, 255);
   Rbend = map(Rbend, RbendMin, RbendMax, 0, 255);
   squeeze = map(squeeze, squeezeMin, squeezeMax, 0, 255);
   */

  Serial.print(Lbend);
  Serial.print(",");
  Serial.print("\t");
  Serial.print(Rbend);
  Serial.print(",");
  Serial.print("\t");
  Serial.print(squeeze);
  Serial.print(",");
  Serial.print("\t");
  Serial.print(x);
  Serial.print(",");
  Serial.print("\t");
  Serial.print(y);
  Serial.print(",");
  Serial.print("\t");
  Serial.print(z);
  Serial.print(",");
  Serial.print("\t");
  Serial.print(tilt1);
  Serial.print(",");
  Serial.print("\t");
  Serial.print(tilt2);
  Serial.print(",");
  Serial.print("\t");
  Serial.print(command);
    Serial.print(",");
  Serial.print("\t");
  Serial.print(key);
  
  Serial.println("");
  //Serial.print("\t");

  // TILT
  if(tilt1 == 1 && tilt2 == 1) key = "up";
  if(tilt1 == 0 && tilt2 == 0) key = "down";
  if(tilt1 == 1 && tilt2 == 0) key = "right";
  if(tilt1 == 0 && tilt2 == 1) key = "left";
  
  // BEND
  if(Rbend < 100) key = "right bend";
  if(Lbend < 100) key = "left bend";
  
  // SQUEEZE
  if(squeeze < 200) key = "squeeze";

  // LED
  if(command == 'r') {
    analogWrite(redLEDPin, 255);
  }
  if(command == 'g') {
    analogWrite(greenLEDPin, 255);
  }
  if(command == 'b') {
    analogWrite(blueLEDPin, 255);
  }


  // VIBE
  if(command == 'v') {
    analogWrite(vibePin, 255);
  }

  // SOUND
  if(command == 's') {
    tone(speakerPin, 1200, 500);
    delay(500);
  }


  // ALL OFF
  if(command == 'o') {
    analogWrite(redLEDPin, 0);
    analogWrite(greenLEDPin, 0);
    analogWrite(blueLEDPin, 0);
    analogWrite(vibePin, 0);
  }

}


void establishContact() {
  if (Serial.available() <= 0) {
    Serial.print('A', BYTE);   // send a capital A
    delay(300);
  }
}





