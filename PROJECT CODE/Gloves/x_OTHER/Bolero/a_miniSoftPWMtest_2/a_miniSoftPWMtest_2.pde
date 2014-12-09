/*Software PWM on arduino mini
 Ernst Christensen 16.okt. 2011
 copied from here: http://arduino.cc/forum/index.php/topic,75334.0.html
 */

String boleroPart = "LeftSleeveLEDs"; 
const int numberLEDs = 14;
int leds[numberLEDs];

int RightSleeveLEDs[]={
  2,3,4,5,6,7,8,9,10,11,12,13,14,15}; //14
int LeftSleeveLEDs[]={
  4,5,6,7,8,9,10,11,12,13,14,15,16,17}; //14
int CollarLEDs[]={
  2,3,4,5,6,7,8,9,10,11,12,13,14,15}; //16
char mode = 'X';

int r[] = {
  9,13,4,17,10,6,13,5,16,15,7,8,11,12};// random variable

int xIMUpin1 = 0;
int xIMUpin2 = 1;
int xIMUpin3 = 18; // = A4
int xIMUpin4 = 19; // = A5

int value1, value2, value3, value4;

int delayTime; // can't be 0!
int delayVariable = 5; // can't be 0!




void setup(){
  Serial.begin(9600); // will interfere with xIMU com.

  for (int z=0;z<numberLEDs;z++) pinMode(LeftSleeveLEDs[z],OUTPUT);

  //pinMode(xIMUpin1, INPUT);
  //digitalWrite(xIMUpin1, HIGH); // internal pullup for triggerpin
  //pinMode(xIMUpin2, INPUT);
  //digitalWrite(xIMUpin2, HIGH); // internal pullup for triggerpin
  pinMode(xIMUpin3, INPUT);
  digitalWrite(xIMUpin3, HIGH); // internal pullup for triggerpin
  pinMode(xIMUpin4, INPUT);
  digitalWrite(xIMUpin4, HIGH); // internal pullup for triggerpin

  // write led pin numbers of current bolero part to led array
  for(int i = 0; i<numberLEDs; i++) leds[i] = LeftSleeveLEDs[i];
}











void loop() {
  mode = Serial.read();
  
start:
  //mode = getMode();
  //listenXIMU();

  for(int i = 0; i<numberLEDs; i++){
    for(int x = 1; x < (254/(mode+1)); x++) {
      delayTime = delayVariable * mode;
      spwm(x,r[i],delayTime);
      spwm(x,r[i+1],delayTime);
      spwm(x,r[i+2],delayTime);
      spwm(x,r[i+3],delayTime);
      //if(getMode() != mode) goto start;
    }
    for(int x = (254/(mode+1)); x > 1; x--) {
      spwm(x,r[i],delayTime);
      spwm(x,r[i+1],delayTime);
      spwm(x,r[i+2],delayTime);
      spwm(x,r[i+3],delayTime);
      //if(getMode() != mode) goto start;
    }
  }
}

char getMode() {
  char lMode = 0;
  value1 = digitalRead(xIMUpin1);
  value2 = digitalRead(xIMUpin2);
  value3 = digitalRead(xIMUpin3);
  value4 = digitalRead(xIMUpin4);
  if(value1==1) lMode |= 0x01;
  if(value2==1) lMode |= 0x01 << 1;
  if(value3==1) lMode |= 0x01 << 2;
  if(value4==1) lMode |= 0x01 << 3;
  return lMode;
 }



/*void switchStatement(){
  switch(mode) {
    case(1):
    allON();
    break;
    case(2):
    allOFF();
    break;
    case(3):
    singleOrder();
    break;
    case(4):
    singleRandom():
      break;
  default:
    groupOrder
      break;  
  }
}
*/



void listenXIMU() {
  value1 = digitalRead(xIMUpin1);
  value2 = digitalRead(xIMUpin2);
  value3 = digitalRead(xIMUpin3);
  value4 = digitalRead(xIMUpin4);

  mode = 0x00;

  //0-15
  if(value1==1) mode |= 0x01;
  if(value2==1) mode |= 0x01 << 1;
  if(value3==1) mode |= 0x01 << 2;
  if(value4==1) mode |= 0x01 << 3;


}





void singleOrder(){
  // in order singles
  for(int i = 0; i<numberLEDs; i++){
    for(int x=1;x<254;x++) {
      spwm(x,leds[i],delayTime);
    }
    for(int x=254;x>1;x--) {
      spwm(x,leds[i],delayTime);
    }
  }
}

void singleRandom(){
  for(int i = 0; i<numberLEDs; i++){
    for(int x=1;x<254;x++) {
      spwm(x,r[i],delayTime);
    }
    for(int x=254;x>1;x--) {
      spwm(x,r[i],delayTime);
    }
  }
}

void groupOrder(){
  for(int i = 0; i<numberLEDs; i++){
    for(int x=1;x<254;x++) {
      spwm(x,leds[i],delayTime);
      spwm(x,leds[i+1],delayTime);
      spwm(x,leds[i+2],delayTime);
      spwm(x,leds[i+3],delayTime);
      spwm(x,leds[i+4],delayTime);
    }
    for(int x=254;x>1;x--) {
      spwm(x,leds[i],delayTime);
      spwm(x,leds[i+1],delayTime);
      spwm(x,leds[i+2],delayTime);
      spwm(x,leds[i+3],delayTime);
      spwm(x,leds[i+4],delayTime);
    }
  }
}

void allFade(){
  for(int x=1;x<254;x++) {
    for(int i = 0; i<numberLEDs; i++){
      spwm(x,leds[i],2);
    }
  }
  for(int x=254;x>1;x--) {
    for(int i = 0; i<numberLEDs; i++){
      spwm(x,leds[i],2);
    }
  }
}

void allOFF(){
  for(int i = 0; i<numberLEDs; i++){
    digitalWrite(leds[i], 0);
  }
}


void allON(){
  for(int i = 0; i<numberLEDs; i++){
    digitalWrite(leds[i], 255);
  }
}






void spwm(int freq,int pin,int sp) {
  //on
  digitalWrite(pin,HIGH);
  delayMicroseconds(sp*freq);
  // off
  digitalWrite(pin,LOW);
  delayMicroseconds(sp*(255-freq));
} //spwm


















