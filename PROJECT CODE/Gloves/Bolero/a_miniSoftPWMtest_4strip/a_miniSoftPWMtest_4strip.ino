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
  if(localMode == 0)
     allOFF();
  else
     ledRandomOn(localMode);
  delay(30);

  //ledPWMState(led);
  //listenXIMU();
  //playLEDs();
  //allFADE();
  //allON();
}






void ledRandomOn(int ledCount) 
{
  int randomNum = random(0, 15 -ledCount);
  if (randomNum == 0)
  {
     allOFF();
     for (int i = 0; i < ledCount; i++)
     {
       int ledIndex = random(0, 16);
       digitalWrite(leds[ledIndex], HIGH); 
     }
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




















