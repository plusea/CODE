/*Software PWM on Attiny85
 Ernst Christensen 16.okt. 2011
 copied from here: http://arduino.cc/forum/index.php/topic,75334.0.html
 */

int led[]={
  2,1,0,3};
int sliderPin = 2;
int count=0;
int delayTime = 18;
int arousalValue = 0;
int aV;
int arousalTimer;


void setup(){
  for (int z=0;z<4;z++){
    pinMode(led[z],OUTPUT);
  } 
  pinMode(4, INPUT);  // setting pin A2 as input interrupts with using pin 2 as output???
  digitalWrite(4, HIGH);  // set internal pullups for digital pin 4 = analog pin 2

}


void loop(){
  arousalValue = analogRead(sliderPin);

  if(arousalValue > 0 && arousalValue < 200) aV = 1;
  if(arousalValue > 200 && arousalValue < 400) aV = 2;
  if(arousalValue > 400 && arousalValue < 600) aV = 3;
  if(arousalValue > 600 && arousalValue < 800) aV = 4;
  if(arousalValue > 800 && arousalValue < 1000) aV = 5;
  if(arousalValue > 1000) aV = 6;

  arousalTimer = aV*3;

  for(int i=0;i<2;i++) {
    int light = int(random(0,4));
    
    for(int x=1;x<254;x++) {
      spwm(x,led[light],arousalTimer);
      if(aV<2) spwm(x,led[light-1],arousalTimer/1.5);
      if(aV<5) spwm(x,led[light+1],arousalTimer/1.5);
    }
    for(int x=254;x>1;x--) {
      spwm(x,led[light],arousalTimer);
      if(aV<2) spwm(x,led[light-1],arousalTimer/3);
      if(aV<4) spwm(x,led[light+1],arousalTimer/2);
    }
  }

  delay(10);
}  // end loop





void spwm(int freq,int pin,int sp){

  //on
  digitalWrite(pin,HIGH);
  delayMicroseconds(sp*freq);

  // off
  digitalWrite(pin,LOW);
  delayMicroseconds(sp*(255-freq));


} //spwm













