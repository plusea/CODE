int ledPin1 = 0;
int ledPin2 = 1;
int increase = 3;
int increaseDirection = 1;
int calibration = 0;
int previous;

void setup()  { 
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  
    delay(100);
  for (int i = 0; i < 8; i++) {
    calibration += chargeTime(PB4);
    delay(20);
  }
  calibration = (calibration + 4) / 8;
} 

void loop()  { 
  if (n > calibration) {
    analogWrite(ledPin1, 255-fadeValue);         
    analogWrite(ledPin2, fadeValue);         
    delay(increase);                            

  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
    analogWrite(ledPin1, fadeValue);         
    analogWrite(ledPin2, 255-fadeValue);         
    delay(increase);                            
  } 

  increase = increase + increaseDirection;

  if(increase == 0) increaseDirection = 1;
  if(increase > 3) increaseDirection = -1;
  }
  
  else {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
  }

}




