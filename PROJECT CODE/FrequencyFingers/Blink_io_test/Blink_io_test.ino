// code for Arduino Micro!

#define ledSensorPin 10
#define multi 2
int sensorValue = 0;
int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated
long blinkFreq = 1000;           // interval at which to blink (milliseconds)

void setup() {                 
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {

  // FIRST READ SENSOR INPUT:
  pinMode(A10, INPUT); 
  sensorValue = analogRead(A10);
  Serial.print(sensorValue);
  Serial.print("\t");
  //sensorValue = constrain(sensorValue, 300,500);
  //Serial.print(sensorValue);
  //Serial.print("\t");
  blinkFreq = map(sensorValue, 300,400, 0, 254);
  Serial.print("\t");
  Serial.println(blinkFreq);
  
  // SECOND WRITE LED OUTPUT:
  pinMode(10, OUTPUT); 
  analogWrite(10, sensorValue);
}


