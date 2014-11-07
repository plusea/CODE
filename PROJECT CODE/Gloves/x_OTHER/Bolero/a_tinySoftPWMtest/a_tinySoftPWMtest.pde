/*Software PWM on Attiny85
 Ernst Christensen 16.okt. 2011
 copied from here: http://arduino.cc/forum/index.php/topic,75334.0.html
 */

int led[]={
  0,1,2,3};
int  numberLEDs = 4;
int count=0;
int delayTime = 1; // can't be 0!
int triggerPin = 4;
int triggerValue;
void setup(){
  for (int z=0;z<numberLEDs;z++){
    pinMode(led[z],OUTPUT);
  } //for z
  pinMode(triggerPin, INPUT);
  digitalWrite(triggerPin, HIGH); // internal pullup for pin2, ADC1

}


void loop(){
  triggerValue = digitalRead(triggerPin);

  if(triggerValue == 1){

    for(int i = 0; i<numberLEDs-1; i++){
      for(int x=1;x<254;x++)  spwm(x,led[i],delayTime);
      for(int x=254;x>1;x--)  spwm(x,led[i],delayTime);
    }
    
        for(int i = numberLEDs; i>0; i--){
      for(int x=1;x<254;x++)  spwm(x,led[i],delayTime);
      for(int x=254;x>1;x--)  spwm(x,led[i],delayTime);
    }
    
    
        for(int i = 0; i<numberLEDs-1; i++){
      analogWrite(led[255], HIGH);
      delay(delayTime);
      analogWrite(led[255], LOW);
      delay(delayTime);
    }
    
        for(int i = numberLEDs; i>0; i--){
      analogWrite(led[255], HIGH);
      delay(delayTime);
      analogWrite(led[255], LOW);
      delay(delayTime);
    }
  }

  else {
    for(int f = 0; f<numberLEDs; f++)  digitalWrite(led[f], LOW);
  }


}


void spwm(int freq,int pin,int sp){

  //on
  digitalWrite(pin,HIGH);
  delayMicroseconds(sp*freq);

  // off
  digitalWrite(pin,LOW);
  delayMicroseconds(sp*(255-freq));


} //spwm








