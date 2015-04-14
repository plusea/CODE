/*Software PWM on Attiny85
 Ernst Christensen 16.okt. 2011
 */

int led[]={
  0,1,2,3,4};
int count=0;
int fadeSpeed=5;


void setup(){
  for (int z=0;z<6;z++){

    pinMode(led[z],OUTPUT);

  } //for z

}


void loop(){

  // LED 0,1:
  for (int x=1;x<254;x++){
    analogWrite(0,x);
    analogWrite(1,255-x);
    delay(10);
  }
  for (int x=254;x>1;x--){
    analogWrite(0,x);
    analogWrite(1,255-x);
    delay(10);
  }

  // LED 2:
  spwm(50,2,10);

  // LED 3:
  spwm(70,3,15);

  // LED 4:
  spwm(200,4,20);
}


void spwm(int freq,int spin,int sp){

  //on
  digitalWrite(spin,HIGH);
  delayMicroseconds(sp*freq);

  // off
  digitalWrite(spin,LOW);
  delayMicroseconds(sp*(255-freq));


} //spwm






