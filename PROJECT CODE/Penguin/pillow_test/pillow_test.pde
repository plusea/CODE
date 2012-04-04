int rPin = 3; // red
int gPin = 5;  // blue
int bPin = 6;  // green

int readPin = A2;

void setup()  { 
  digitalWrite(16, HIGH);
  pinMode(2,OUTPUT);
  // nothing happens in setup 
  Serial.begin(9600);
} 

void loop()  { 
  colours();
  //fade();
  //digitalWrite(2, HIGH);
  Serial.println(analogRead(readPin));
  delay(100);
}

void colours(){
  
    //pink
  analogWrite(3, 75);
  analogWrite(6, 0);
  analogWrite(5, 255);
  delay(1000);
  
  //orange
  analogWrite(3, 150);
  analogWrite(6, 200);
  analogWrite(5, 0);
  delay(1000);

  //light blue
  analogWrite(3, 0);
  analogWrite(6, 150);
  analogWrite(5, 100);
  delay(1000);

  // white
  analogWrite(3, 50);
  analogWrite(6, 255);
  analogWrite(5, 255);
  delay(1000);

  //yellow
  analogWrite(3, 50);
  analogWrite(6, 255);
  analogWrite(5, 0);
  delay(1000);

}

void fade(){

  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
    analogWrite(rPin, fadeValue);
    analogWrite(gPin, fadeValue);    
    analogWrite(bPin, fadeValue);
    delay(30);                            
  } 

  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) { 
    analogWrite(rPin, fadeValue);
    analogWrite(gPin, fadeValue);    
    analogWrite(bPin, fadeValue);
    delay(30);                            
  } 
}





