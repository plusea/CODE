#define potPin 2  //test
#define speakerPin 0      //pwm out

#define pinOn() PORTB |= 0b00000001
#define pinOff() PORTB &= ~0b00000001

void setup() {
  pinMode(speakerPin, OUTPUT);  
  pinMode(potPin, INPUT);
  digitalWrite(4, HIGH);  // sets pull-up for adc2
}

void loop() {
  int micValue = analogRead(potPin);
  myBeep(micValue);
  //delay(100);

}

void myBeep(unsigned int freq){
 float halfT = 1000000.f / ((float)freq * 2.f);
 unsigned int numLoop = freq / 10;

  for (int x = 0; x < numLoop; x++){
    pinOn();
    delayMicroseconds(halfT);
    pinOff();
    delayMicroseconds(halfT);
  }
}
/*
  int micValue = analogRead(potPin);
 //micValue = map(micValue, 0,1023, 0,255);
 beep(micValue);
 //analogWrite(speakerPin, micValue);
 }
 
 
 void beep (int freq)     // the sound producing function
 { 	   	 
 //  long delayAmount = (long)(1000000/freq);
 //  long loopTime = (long)((500)/(delayAmount*2));
 for (int x = 0; x < 10000; x++) 	 
 { 	 
 pinOn();
 //delayMicroseconds(1);
 pinOff();
 //delayMicroseconds(1);
 } 	 
 } 
 */




