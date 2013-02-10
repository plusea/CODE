// code for LilyPad IN --- OUT example

#define sensorPin A5
#define actuatorPin 9
#define threshold 300
int sensorValue = 0;


void setup() {
  pinMode(actuatorPin, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(actuatorPin, LOW);
  digitalWrite(A5, HIGH);  
  Serial.begin(9600);
}

void loop() {


sensorValue = analogRead(sensorPin);    
Serial.println(sensorValue);
delay(20);
if(sensorValue < threshold) {
digitalWrite(actuatorPin, HIGH); 
  digitalWrite(13, HIGH);
}
else {
  digitalWrite(actuatorPin, LOW);  
    digitalWrite(13, LOW);
}
}


