/*Software PWM on Attiny85
 Ernst Christensen 16.okt. 2011
 copied from here: http://arduino.cc/forum/index.php/topic,75334.0.html
 */

int led[]={
  2,1,0,3};
int buttonPin = 2;
int arousalValue = 0;
int arousalStage = 0;
boolean buttonPressed = false;

void setup(){
  for (int z=0;z<4;z++){
    pinMode(led[z],OUTPUT);
  } 
  pinMode(4, INPUT);  // setting pin A2 as input interrupts with using pin 2 as output???
  digitalWrite(4, HIGH);  // set internal pullups for digital pin 4 = analog pin 2

}


void loop(){
  arousalValue = analogRead(buttonPin);

  if(arousalValue < 400 && arousalValue > 100 && buttonPressed == false) {
    buttonPressed = true;
    arousalStage++;
    if(arousalStage > 3) arousalStage = 3;
    delay(10);
  }
  if(arousalValue < 100 && arousalValue > 0 && buttonPressed == false) {
    buttonPressed = true;
    arousalStage--;
    if(arousalStage < 0) arousalStage = 0;
    delay(10);
  }
  if(arousalValue > 400) buttonPressed = false;

  //if(arousalStage != 0) {
  int light = int(random(0,4));   // pick a random pin(s) to trigger

  // fade on
  for(int x=1;x<254;x++) {
    if(arousalStage > 0) spwm(x,led[light],18);
    if(arousalStage > 1) spwm(x,led[light-1],3);
    if(arousalStage > 2) spwm(x,led[light+1],1);
  }

  // fade off
  for(int x=254;x>1;x--) {
    if(arousalStage > 0) spwm(x,led[light],18);
    if(arousalStage > 1) spwm(x,led[light-1],3);
    if(arousalStage > 2) spwm(x,led[light+1],1);
  }
  //}

}  // end loop





void spwm(int freq,int pin,int sp){

  //on
  digitalWrite(pin,HIGH);
  delayMicroseconds(sp*freq);

  // off
  digitalWrite(pin,LOW);
  delayMicroseconds(sp*(255-freq));


} //spwm
















