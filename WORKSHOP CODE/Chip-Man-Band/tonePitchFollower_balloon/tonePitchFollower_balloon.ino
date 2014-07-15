// code for balloon sensor made at F-A-S-T workshop in dresden

int sensorMax = 880;
int sensorMin = 760;
int motor = 7;
int motorGND = 6;

void setup() {
  Serial.begin(9600);
  //pinMode(A0, INPUT_PULLUP);
  pinMode(motor, OUTPUT);
  pinMode(motorGND, OUTPUT);
  digitalWrite(motorGND, LOW);
}

void loop() {
  int sensorReading = analogRead(A0);
  int thisPitch = map(sensorReading, sensorMin, sensorMax, 5000, 100);
  int thisGraph = map(sensorReading, sensorMin, sensorMax, 0, 1023);
  thisGraph = constrain(thisGraph, 0, 1023);

  if(sensorReading < sensorMax && sensorReading > sensorMin) {
    tone(9, thisPitch);
    digitalWrite(motor, HIGH);
  }
  else {
    noTone(9);
    digitalWrite(motor, LOW);  
  }

  //Serial.println(thisGraph);
  // Serial.println(thisPitch);  
  Serial.println(sensorReading);  
}







