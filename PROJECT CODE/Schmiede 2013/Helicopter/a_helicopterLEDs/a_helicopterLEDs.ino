/*Software PWM on Attiny85
 Ernst Christensen 16.okt. 2011
 */

int numberLEDs = 5;
int topLED = 3;
int backLED = 4;
int frontLED_1 = 0;
int frontLED_2 = 1;
int frontLED_3 = 2;
int delayTime = 1;
int counter = 0;
int fadeCounter =0;

void setup(){
  for(int z=0;z<numberLEDs;z++) pinMode(z, OUTPUT);
  digitalWrite(frontLED_1, HIGH);
  digitalWrite(frontLED_2, HIGH);
  digitalWrite(frontLED_3, HIGH);

}


void loop(){
  counter++;
  //  if(counter % 100 == 0) fadeCounter++;
  if(counter % 1500 == 0) digitalWrite(topLED,HIGH);
  if(counter % 3000 == 0) digitalWrite(topLED,LOW);

  if(counter % 10000 == 0) digitalWrite(backLED,HIGH);
  if(counter % 20000 == 0) digitalWrite(backLED,LOW);

  if(counter > 2000000000) counter = 0;
  //  if(fadeCounter > 255) fadeCounter = 0;

  //  for (int x=1;x<254;x++) spwm(x,backLED,backDelay);
  //  for (int x=254;x>1;x--) spwm(x,backLED,backDelay);


}







// software PWM
void spwm(int freq,int pin,int sp){
  // call charlieplexing to set correct pin outs:
  //on:
  digitalWrite(pin,HIGH);
  delayMicroseconds(sp*freq);
  // off:
  digitalWrite(pin,LOW);
  delayMicroseconds(sp*(255-freq));
}





















