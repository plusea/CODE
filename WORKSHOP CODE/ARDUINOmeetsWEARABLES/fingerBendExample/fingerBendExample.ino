/*
Reads analog input and turns on 1, 2 or 3 leds depending on 
*/

int sensorPin = A2;
int ledPin1 = 6;
int ledPin2 = 9;
int ledPin3 = 10;
int sensorValue = 0;

void setup() {
  pinMode(ledPin1, OUTPUT);  
  pinMode(ledPin2, OUTPUT);  
  pinMode(ledPin3, OUTPUT);  
  pinMode(sensorPin, INPUT_PULLUP); //turn on internal pull-up resistor
  Serial.begin(9600);
}

void loop() {
 sensorValue = analogRead(sensorPin);   
 Serial.println(sensorValue); 
   //delay(100); 
  if(sensorValue > 900) digitalWrite(ledPin3, HIGH);
  if(sensorValue > 500) digitalWrite(ledPin2, HIGH);
  if(sensorValue > 300) digitalWrite(ledPin1, HIGH);
  if (sensorValue <= 300){
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
  }
  
 
}
