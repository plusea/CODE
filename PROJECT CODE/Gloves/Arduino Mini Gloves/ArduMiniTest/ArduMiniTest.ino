// test code for Arduino Gloves
// http://www.plusea.at/?category_name=gloves

#define redPin 3
#define bluePin 6
#define greenPin 9
#define ledGNDpin 2
#define vibrationPin 10
#define vibrationGNDpin 11

// finger bend sensors
int thumb;
int indexH;
int indexF;
int middleH;
int middleF;
int ringH;
int ringF;
int little;

// RGB led values
int red;
int green;
int blue;

// motor value
int vibration;




void setup() {                
  pinMode(vibrationPin, OUTPUT);    
  pinMode(vibrationGNDpin, OUTPUT);  
  //pinMode(BStriStatePin1, OUTPUT);    
  //pinMode(BStriStatePin2, OUTPUT);    
  pinMode(ledGNDpin, OUTPUT);    
  pinMode(redPin, OUTPUT);    
  pinMode(greenPin, OUTPUT);    
  pinMode(bluePin, OUTPUT); 

  // set pull-up resistors for bend sensors
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(16, HIGH);
  digitalWrite(17, HIGH);

  //Serial.begin(9600);  //USB
  Serial.begin(115200);  //Bluetooth
}


void loop() {
  for(int i=0; i<8; i++) {
    readFinger(i);
  }

  Serial.print(thumb);
  Serial.print(",");
  Serial.print(indexH);
  Serial.print(",");
  Serial.print(indexF);
  Serial.print(",");
  Serial.print(middleH);
  Serial.print(",");
  Serial.print(middleF);
  Serial.print(",");
  Serial.print(ringH);
  Serial.print(",");
  Serial.print(ringF);
  Serial.print(",");
  Serial.print(little);
  Serial.println();
}




void readFinger(int fingerNumber) {

  // thumb:
  if(fingerNumber == 0) {
    pinMode(12, OUTPUT);
    digitalWrite(12, LOW);
    pinMode(13, INPUT);
    digitalWrite(13, HIGH);
    delay(2);
    thumb=analogRead(A0);
  }

  // indexH:
  if(fingerNumber == 1) {
    pinMode(12, OUTPUT);
    digitalWrite(12, LOW);
    pinMode(13, INPUT);
    digitalWrite(13, HIGH);
    delay(2);
    indexH=analogRead(A1);
  }

  // indexF:
  if(fingerNumber == 2) {
    pinMode(12, OUTPUT);
    digitalWrite(12, LOW);
    pinMode(13, INPUT);
    digitalWrite(13, HIGH);
    delay(2);
    indexF=analogRead(A2);
  }

  // middleH:
  if(fingerNumber == 3) {
    pinMode(12, OUTPUT);
    digitalWrite(12, LOW);
    pinMode(13, INPUT);
    digitalWrite(13, HIGH);
    delay(2);
    middleH=analogRead(A3);
  }

  // middleF:
  if(fingerNumber == 4) {
    pinMode(12, INPUT);
    digitalWrite(12, HIGH);
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
    delay(2);
    middleF=analogRead(A0);
  }
  
    // ringH:
  if(fingerNumber == 5) {
    pinMode(12, INPUT);
    digitalWrite(12, HIGH);
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
    delay(2);
    ringH=analogRead(A1);
  }
  
    // ringF:
  if(fingerNumber == 6) {
    pinMode(12, INPUT);
    digitalWrite(12, HIGH);
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
    delay(2);
    ringF=analogRead(A2);
  }
  
    // little:
  if(fingerNumber == 7) {
    pinMode(12, INPUT);
    digitalWrite(12, HIGH);
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
    delay(2);
    little=analogRead(A3);
  }

}




