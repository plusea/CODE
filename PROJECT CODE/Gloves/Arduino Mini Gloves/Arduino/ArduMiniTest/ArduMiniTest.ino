// test code for Arduino Gloves
// http://www.plusea.at/?category_name=gloves

//true for LEFT HAND
#define redPin 6
#define bluePin 9
#define greenPin 3
#define ledGNDpin 2
#define vibrationPin 10
#define vibrationGNDpin 11

// finger bend sensors
int sensor[8] = {
};
int sensorMin[8] = {
};
int sensorMax[8] = {
};

// RGB led values
int red;
int green;
int blue;

// motor value
int vibration;




void setup() {    
  pinMode(vibrationPin, OUTPUT);    
  pinMode(vibrationGNDpin, OUTPUT);  
  digitalWrite(vibrationGNDpin, LOW);
  pinMode(ledGNDpin, OUTPUT); 
  digitalWrite(ledGNDpin, LOW);  
  pinMode(redPin, OUTPUT);    
  pinMode(greenPin, OUTPUT);    
  pinMode(bluePin, OUTPUT); 

  // set pull-up resistors for bend sensors
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(16, HIGH);
  digitalWrite(17, HIGH);

  //////////////////////////////////////////////////////////////////////////////////////////
  digitalWrite(redPin, HIGH);  //turn on red LED when collecting BS values

  for(int i=0; i<8; i++) {  //read all BS values once
    readSensor(i);
    sensorMin[i] = sensor[i];  //initialize sensor MAXs to value of first sensor reading
    sensorMax[i] = sensor[i];  //initialize sensor MINs to value of first sensor reading
  }

  // determine min and max of bend sensor values
  while(millis() < 3000){  
    for(int i=0; i<8; i++) {  //read all BS values once
      readSensor(i);
      if(sensor[i] < sensorMin[i]) sensorMin[i] = sensor[i];  //update sensor MINs
      if(sensor[i] > sensorMax[i]) sensorMax[i] = sensor[i];  //update sensor MAXs
    }
  }
  digitalWrite(redPin, LOW);  //turn off red LED when finished collecting BS values
  //////////////////////////////////////////////////////////////////////////////////////////

  //Serial.begin(9600);  //USB
  Serial.begin(115200);  //USB or Bluetooth

  for(int i=0; i<8; i++) {  //print all MINs and MAXs sensor values
    Serial.print(i);
    Serial.print("\t");
    Serial.print("min: ");
    Serial.print(sensorMin[i]);
    Serial.print("\t");
    Serial.print("max: ");
    Serial.print(sensorMax[i]);
    Serial.println();
  }

}


void loop() {
  for(int i=0; i<8; i++) {
    readSensor(i);
  }

  mapSensorValues();
  sendSerial();

  red = map(sensor[2], sensorMin[2], sensorMax[2], 0, 255);
  green = map(sensor[4], sensorMin[4], sensorMax[4], 0, 255);
  blue = map(sensor[6], sensorMin[6], sensorMax[6], 0, 255);
  vibration = map(sensor[0], sensorMin[0], sensorMax[0], 0, 255);

  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
  analogWrite(vibrationPin, vibration);
}


void sendSerial(){
  for(int i=0; i<8; i++) {
    Serial.print(sensor[i]);
    if(i<7)Serial.print(",");
  }
  Serial.println();
}

void mapSensorValues(){
  for(int i=0; i<8; i++) {
    sensor[i] = constrain(sensor[i], sensorMin[i], sensorMax[i]);
    sensor[i] = map(sensor[i], sensorMin[i], sensorMax[i], 0, 1023);
  }
}

void printSerial(){
  for(int i=0; i<8; i++) {
    Serial.print(i);
    Serial.print(": ");
    Serial.print(sensor[i]);
    Serial.print("\t");
  }
  Serial.println();
}


void readSensor(int BSnumber) {

  // thumb:
  if(BSnumber == 0) {
    pinMode(12, OUTPUT);
    digitalWrite(12, LOW);
    pinMode(13, INPUT);
    digitalWrite(13, HIGH);
    delay(2);
    sensor[BSnumber]=analogRead(A0);
  }

  // indexH:
  if(BSnumber == 1) {
    pinMode(12, OUTPUT);
    digitalWrite(12, LOW);
    pinMode(13, INPUT);
    digitalWrite(13, HIGH);
    delay(2);
    sensor[BSnumber]=analogRead(A1);
  }

  // indexF:
  if(BSnumber == 2) {
    pinMode(12, OUTPUT);
    digitalWrite(12, LOW);
    pinMode(13, INPUT);
    digitalWrite(13, HIGH);
    delay(2);
    sensor[BSnumber]=analogRead(A2);
  }

  // middleH:
  if(BSnumber == 3) {
    pinMode(12, OUTPUT);
    digitalWrite(12, LOW);
    pinMode(13, INPUT);
    digitalWrite(13, HIGH);
    delay(2);
    sensor[BSnumber]=analogRead(A3);
  }

  // middleF:
  if(BSnumber == 4) {
    pinMode(12, INPUT);
    digitalWrite(12, HIGH);
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
    delay(2);
    sensor[BSnumber]=analogRead(A0);
  }

  // ringH:
  if(BSnumber == 5) {
    pinMode(12, INPUT);
    digitalWrite(12, HIGH);
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
    delay(2);
    sensor[BSnumber]=analogRead(A1);
  }

  // ringF:
  if(BSnumber == 6) {
    pinMode(12, INPUT);
    digitalWrite(12, HIGH);
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
    delay(2);
    sensor[BSnumber]=analogRead(A2);
  }

  // little:
  if(BSnumber == 7) {
    pinMode(12, INPUT);
    digitalWrite(12, HIGH);
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
    delay(2);
    sensor[BSnumber]=analogRead(A3);
  }

}













