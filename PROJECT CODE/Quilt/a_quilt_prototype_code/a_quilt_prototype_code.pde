/*
sound code for quilt prototype
 */

int storeValues[48];
int playTones [] = {
  10,100,150,500,1000,2000};  //tones
int beadsIN [] = {
  4,3,2,16,15,14,13,12};  //inputs
int petalsOUT [] = {
  5,6,7,8,9,10};  //outputs
int speakerPin = 11;
int petalCount;
int reading;

void setup() {   
  for(int i; i< 8; i++){
    digitalWrite(beadsIN[i], HIGH);
  }
  for(int i; i< 6; i++){
    pinMode(petalsOUT[i], OUTPUT);
  }
  pinMode(speakerPin, OUTPUT);     
  noTone(speakerPin);

  Serial.begin(9600);
}

void loop() {
  for(int i; i< 6; i++){
    digitalWrite(petalsOUT[i], HIGH);
  }
  digitalWrite(petalsOUT[petalCount], LOW);


  for(int i; i< 8; i++){
    reading = digitalRead(beadsIN[i]);

    if(reading != storeValues[(petalCount*8) + i] && reading == 0) {
      tone(speakerPin, i * playTones[petalCount], 1000);
      delay(1000);
      Serial.print("*");
    }

    storeValues[(petalCount*8) + i] = reading;
    
    Serial.print(reading);
    Serial.print(",");
    //Serial.print("\t");

    }

    Serial.println("");

  petalCount++;
  if(petalCount == 8) {
    petalCount = 0;
    Serial.println("--------------------");
  }
}

