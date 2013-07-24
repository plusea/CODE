// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.

int swimmSensor2; 

void setup() 
{ 
  pinMode(A5, INPUT_PULLUP);
  pinMode(5, OUTPUT);
  Serial.begin(9600);
} 


void loop() 
{ 
  swimmSensor2 = analogRead(A5);
  Serial.println(swimmSensor2);
  if(swimmSensor2 < 900) {
    tone(5, swimmSensor2);
    digitalWrite(13, HIGH);

  }
  else {
    noTone(5);
    digitalWrite(13, LOW);
  }


} 





