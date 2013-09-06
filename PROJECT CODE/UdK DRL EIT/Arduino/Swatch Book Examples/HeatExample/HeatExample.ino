// UdK DRL EIT
// code that reads value of analog sensor and triggers digital output

int sensorPin = 3;    // select the input pin for the potentiometer
int heatPin = 4;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(sensorPin, INPUT); 
  digitalWrite(sensorPin, HIGH);
 pinMode(heatPin, OUTPUT);  
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);    
  if(sensorValue < 500) digitalWrite(heatPin, HIGH);
  else digitalWrite(heatPin, LOW);  
}
