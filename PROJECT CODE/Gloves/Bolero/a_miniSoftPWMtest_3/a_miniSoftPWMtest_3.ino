/*Software PWM on arduino mini
 Ernst Christensen 16.okt. 2011
 copied from here: http://arduino.cc/forum/index.php/topic,75334.0.html
 */

int leds[]={
  2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17}; //16
const int numberLEDs = 16;

int RightSleeveLEDs[]={
  2,3,4,5,6,7,8,9,10,11,12,13,14,15}; //14
int LeftSleeveLEDs[]={
  4,5,6,7,8,9,10,11,12,13,14,15,16,17}; //14
int CollarLEDs[]={
  2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17}; //16


char xIMUmode = 'X';
int mode;

int r[] = {
  2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17}; //16
int rLength = 20;

int xIMUpin1 = 0;
int xIMUpin2 = 1;
int xIMUpin3 = 18; // = A4
int xIMUpin4 = 19; // = A5

int value1, value2, value3, value4;

int delayTime = 1; // can't be 0!
int delayVariable = 1; // can't be 0!




void setup(){
  //Serial.begin(9600); // will interfere with xIMU comunication!!!

  for (int z=0;z<numberLEDs;z++) pinMode(leds[z],OUTPUT);

  // set x-IMU pins as inputs and set pull-up resistors
  pinMode(xIMUpin1, INPUT);
  digitalWrite(xIMUpin1, HIGH); // internal pullup for triggerpin
  pinMode(xIMUpin2, INPUT);
  digitalWrite(xIMUpin2, HIGH); // internal pullup for triggerpin
  pinMode(xIMUpin3, INPUT);
  digitalWrite(xIMUpin3, HIGH); // internal pullup for triggerpin
  pinMode(xIMUpin4, INPUT);
  digitalWrite(xIMUpin4, HIGH); // internal pullup for triggerpin
}











void loop() {
  //mode = Serial.read();  // test

  interpretMode();

  //listenXIMU();
  //playLEDs();
  //allFADE();
  //allON();
}


char getMode() {
  char lMode = 0;
  value1 = digitalRead(19);
  value2 = digitalRead(18);
  value3 = digitalRead(0);
  value4 = digitalRead(1);
  if(value1==1) lMode |= 0x01;
  if(value2==1) lMode |= 0x01 << 1;
  if(value3==1) lMode |= 0x01 << 2;
  if(value4==1) lMode |= 0x01 << 3;
  return lMode;
}


void interpretMode() {
  mode = getMode();
  for(int i=0; i<16; i++){
    if(mode > i+1) digitalWrite(r[i], HIGH); 
    else digitalWrite(r[i], LOW);
  }
}







void interpretModeSPWM() {
  mode = getMode();
  int i = 0;
  for(int x=1; x<254; x++) {
    if(mode==0) {
    }
    if(mode>0) spwm(x,r[i+1],delayTime);
    if(mode>1) spwm(x,r[i+2],delayTime);
    if(mode>2) spwm(x,r[i+3],delayTime);
    if(mode>3) spwm(x,r[i+4],delayTime);
    if(mode>4) spwm(x,r[i+5],delayTime);
    if(mode>5) spwm(x,r[i+6],delayTime);
    if(mode>6) spwm(x,r[i+7],delayTime);
    if(mode>7) spwm(x,r[i+8],delayTime);
    if(mode>8) spwm(x,r[i+9],delayTime);
    if(mode>9) spwm(x,r[i+10],delayTime);
    if(mode>10) spwm(x,r[i+11],delayTime);
    if(mode>11) spwm(x,r[i+12],delayTime);
    if(mode>12) spwm(x,r[i+13],delayTime);
    if(mode>13) spwm(x,r[i+14],delayTime);
    if(mode>14) spwm(x,r[i+15],delayTime);

    //if(getMode() != mode) goto start;
  }

  // fade out:
  for(int x=254; x>1; x--) {
    if(mode==0) {
    }
    if(mode>0) spwm(x,r[i+1],delayTime);
    if(mode>1) spwm(x,r[i+2],delayTime);
    if(mode>2) spwm(x,r[i+3],delayTime);
    if(mode>3) spwm(x,r[i+4],delayTime);
    if(mode>4) spwm(x,r[i+5],delayTime);
    if(mode>5) spwm(x,r[i+6],delayTime);
    if(mode>6) spwm(x,r[i+7],delayTime);
    if(mode>7) spwm(x,r[i+8],delayTime);
    if(mode>8) spwm(x,r[i+9],delayTime);
    if(mode>9) spwm(x,r[i+10],delayTime);
    if(mode>10) spwm(x,r[i+11],delayTime);
    if(mode>11) spwm(x,r[i+12],delayTime);
    if(mode>12) spwm(x,r[i+13],delayTime);
    if(mode>13) spwm(x,r[i+14],delayTime);
    if(mode>14) spwm(x,r[i+15],delayTime);
    //if(getMode() != mode) goto start;
  }

}



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








void playLEDs(){
  for(int i = 0; i<rLength; i++){

    // change delayTime depending on mode?:
    //delayTime = delayVariable * mode;
    mode++;
    // fade in:
    for(int x=1; x<254; x++) {
      if(mode > 16) mode = 0;
      if(mode>0) spwm(x,r[i],delayTime);
      if(mode>1) spwm(x,r[i+1],delayTime);
      if(mode>2) spwm(x,r[i+2],delayTime);
      if(mode>3) spwm(x,r[i+3],delayTime);
      if(mode>4) spwm(x,r[i+4],delayTime);
      if(mode>5) spwm(x,r[i+5],delayTime);
      if(mode>6) spwm(x,r[i+6],delayTime);
      if(mode>7) spwm(x,r[i+7],delayTime);
      if(mode>8) spwm(x,r[i+8],delayTime);
      if(mode>9) spwm(x,r[i+9],delayTime);
      if(mode>10) spwm(x,r[i+10],delayTime);
      if(mode>11) spwm(x,r[i+11],delayTime);
      if(mode>12) spwm(x,r[i+12],delayTime);
      if(mode>13) spwm(x,r[i+13],delayTime);
      if(mode>14) spwm(x,r[i+14],delayTime);
      if(mode>15) spwm(x,r[i+15],delayTime);

      //if(getMode() != mode) goto start;
    }

    // fade out:
    for(int x=254; x>1; x--) {
      if(mode>0) spwm(x,r[i],delayTime);
      if(mode>1) spwm(x,r[i+1],delayTime);
      if(mode>2) spwm(x,r[i+2],delayTime);
      if(mode>3) spwm(x,r[i+3],delayTime);
      if(mode>4) spwm(x,r[i+4],delayTime);
      if(mode>5) spwm(x,r[i+5],delayTime);
      if(mode>6) spwm(x,r[i+6],delayTime);
      if(mode>7) spwm(x,r[i+7],delayTime);
      if(mode>8) spwm(x,r[i+8],delayTime);
      if(mode>9) spwm(x,r[i+9],delayTime);
      if(mode>10) spwm(x,r[i+10],delayTime);
      if(mode>11) spwm(x,r[i+11],delayTime);
      if(mode>12) spwm(x,r[i+12],delayTime);
      if(mode>13) spwm(x,r[i+13],delayTime);
      if(mode>14) spwm(x,r[i+14],delayTime);
      if(mode>15) spwm(x,r[i+15],delayTime);
      //if(getMode() != mode) goto start;
    }
  }
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

void allFADE(){
  for(int x=1;x<254;x++) {
    for(int i = 0; i<numberLEDs; i++) spwm(x,leds[i],delayTime);
  }
  for(int x=254;x>1;x--) {
    for(int i = 0; i<numberLEDs; i++) spwm(x,leds[i],delayTime);
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


















