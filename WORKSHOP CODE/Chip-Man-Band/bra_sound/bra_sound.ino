// code for balloon sensor made at F-A-S-T workshop in dresden

int harpPin1 = 6;
int harpPin2 = 7;
int harpPin3 = 8;
int harpPin4 = 9;
int harpPin5 = 10;
int squeezeSensorPin = A0;
int squeezeThreshold = 350;
int speakerPin = 4;


void setup() {
  Serial.begin(9600);
  pinMode(harpPin1, INPUT_PULLUP);
  pinMode(harpPin2, INPUT_PULLUP);
  pinMode(harpPin3, INPUT_PULLUP);
  pinMode(harpPin4, INPUT_PULLUP);
  pinMode(harpPin5, INPUT_PULLUP);
  pinMode(squeezeSensorPin, INPUT);
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  ////// HARP /////
  int harpValue1 = digitalRead(harpPin1);
  int harpValue2 = digitalRead(harpPin2);
  int harpValue3 = digitalRead(harpPin3);
  int harpValue4 = digitalRead(harpPin4);
  int harpValue5 = digitalRead(harpPin5);

  ///// SQUEEZE /////
  int squeezeValue = analogRead(squeezeSensorPin);

  ///// TONE /////
  if (squeezeValue > squeezeThreshold) tone(speakerPin, squeezeValue);
  else if(harpValue1 == 0) tone(speakerPin, 1000);
  else if(harpValue2 == 0) tone(speakerPin, 2000);
  else if(harpValue3 == 0) tone(speakerPin, 3000);
  else if(harpValue4 == 0) tone(speakerPin, 4000);
  else if(harpValue5 == 0) tone(speakerPin, 5000);
  else noTone(speakerPin);

  ///// SERIAL /////
  Serial.print(squeezeValue); 
  Serial.print("     ");
  Serial.print(harpValue1); 
  Serial.print("     "); 
  Serial.print(harpValue2); 
  Serial.print("     "); 
  Serial.print(harpValue3); 
  Serial.print("     "); 
  Serial.print(harpValue4); 
  Serial.print("     "); 
  Serial.println(harpValue5); 
}










