/*Software PWM on arduino mini
 Ernst Christensen 16.okt. 2011
 copied from here: http://arduino.cc/forum/index.php/topic,75334.0.html
 */

int leds[]={
  2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17}; //16
const int numberLEDs = 16;


int r[] = {
  2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17}; //16
int rLength = 20;
int RightSleeveLEDs[]={
  2,3,4,5,6,7,8,9,10,11,12,13,14,15}; //14
int LeftSleeveLEDs[]={
  4,5,6,7,8,9,10,11,12,13,14,15,16,17}; //14
int CollarLEDs[]={
  2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17}; //16

unsigned char ledValues[16];

int mode;

int xIMUpin1 = 19;
int xIMUpin2 = 18;
int xIMUpin3 = 0; // = A4
int xIMUpin4 = 1; // = A5

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

  int localMode = getMode();
  //allON();
  ledPWMState(localMode);
  delay(100);

  //ledPWMState(led);
  //listenXIMU();
  //playLEDs();
  //allFADE();
  //allON();
}

void updatePWM()
{

}


void ledPWMState(int ledCount) 
{
  allOFF();
  for (int i = 0; i < ledCount; i++)
  {
    int ledIndex = random(0, 16);
    digitalWrite(leds[ledIndex], HIGH); 
  }
}






void interpretModeSPWM() {


  for(int x=1; x<254; x++) {
    
    for(int i=0; i<16; i++){
      
      mode = getMode();
      
      if(mode==0) {
      }
      if(mode > i+1) spwm(x,leds[i],delayTime);
    }
    //if(getMode() != mode) goto start;
  }

  // fade out:
  for(int x=254; x>1; x--) {

    for(int i=0; i<16; i++){
     
      mode = getMode();
     
      if(mode==0) {
      }
      
      if(mode > i+1) spwm(x,leds[i],delayTime);
    }
    //if(getMode() != mode) goto start;
  }

}







void ledOn(int ledIndex) 
{
  for(int i=0; i<16; i++)
  {
    if(i == ledIndex) 
       digitalWrite(r[i], HIGH); 
    else
       digitalWrite(r[i], LOW);
  }
}

void ledPWMState(int ledIndex, boolean state) 
{
  if(state == true)
       digitalWrite(r[ledIndex], HIGH); 
    else
       digitalWrite(r[ledIndex], LOW);
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



















