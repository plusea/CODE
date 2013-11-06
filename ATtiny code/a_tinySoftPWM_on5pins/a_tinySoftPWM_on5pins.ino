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

  for (int x=1;x<254;x++){
    spwm(x,led[count],fadeSpeed);
  }
  for (int x=254;x>1;x--){
    spwm(x,led[count],fadeSpeed);
  }

  count++;
  if (count>4){
    count=0;
  }

}


void spwm(int freq,int spin,int sp){

  //on
  digitalWrite(spin,HIGH);
  delayMicroseconds(sp*freq);

  // off
  digitalWrite(spin,LOW);
  delayMicroseconds(sp*(255-freq));


} //spwm



