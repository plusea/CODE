int RbendPin = A0;
int LbendPin = A1;
int squeezePin = A3;
int vibePin = 3; // PWM
int blueLEDPin = 5; // PWM
int yellowLEDPin = 9; // PWM
int speakerPin = 8;
int RtiltPin = 7;
int LtiltPin = 6;
int Rbend, Lbend, squeeze, Rtilt, Ltilt;
int RbendMax = 500;
int RbendMin = 70;
int LbendMax = 500;
int LbendMin = 70;
int squeezeMax = 160;
int squeezeMin = 80;
int inByte;

void setup() {
  pinMode(blueLEDPin, OUTPUT);
  pinMode(yellowLEDPin, OUTPUT);
  pinMode(speakerPin, OUTPUT);
  pinMode(vibePin, OUTPUT);
  // set pullup resistors:
  digitalWrite(14,HIGH);
  digitalWrite(15,HIGH);
  digitalWrite(17,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);

  Serial.begin(9600);
  //Serial.begin(115200);
  
  establishContact();  // send a byte to establish contact until receiver responds 

  noTone(speakerPin);
}

void loop() {

  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();
  }

  Lbend = analogRead(LbendPin);
  Rbend = analogRead(RbendPin);
  squeeze = analogRead(squeezePin);
  Ltilt = digitalRead(LtiltPin);
  Rtilt= digitalRead(RtiltPin);

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
  Serial.print(Rbend);
  Serial.print(",");
  Serial.print(squeeze);
  Serial.print(",");
  Serial.print(Ltilt);
  Serial.print(",");
  Serial.print(Rtilt);
  Serial.print(",");
  Serial.print(inByte);
  Serial.println("");
  //Serial.print("\t");

  //analogWrite(blueLEDPin, 255-Lbend);
  //analogWrite(yellowLEDPin, 255-Rbend);
  //analogWrite(vibePin, 255-squeeze);

  if(inByte == 49) {
    tone(speakerPin, 1200, 500);
    delay(500);
  }
  if(inByte == 50) {
    tone(speakerPin, 1400, 500);
    delay(500);
  }
  if(inByte == 51) {
    tone(speakerPin, 1600, 500);
    delay(500);
  }
  if(inByte == 52) noTone(speakerPin);

  if(inByte == 53) analogWrite(blueLEDPin, 255);
  if(inByte == 54) analogWrite(blueLEDPin, 0);
  
  if(inByte == 55) analogWrite(yellowLEDPin, 255);
  if(inByte == 56) analogWrite(yellowLEDPin, 0);
  
  if(inByte == 57) analogWrite(vibePin, 255);
  if(inByte == 48) analogWrite(vibePin, 0);
}


void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('A', BYTE);   // send a capital A
    delay(300);
  }
}




