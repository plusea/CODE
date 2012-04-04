/*Software PWM on Attiny85
 Ernst Christensen 16.okt. 2011
 copied from here: http://arduino.cc/forum/index.php/topic,75334.0.html
 */

int delayTime = 18;

void setup(){
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
}


void loop(){

    
    
        for (int x=1;x<254;x++){
      analogWrite(1,x);
  delay(30);  
    }

    for (int x=254;x>1;x--){
      analogWrite(1,x);
        delay(30);  
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








