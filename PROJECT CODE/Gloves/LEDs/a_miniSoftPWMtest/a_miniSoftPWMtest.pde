/*Software PWM on arduino mini
 Ernst Christensen 16.okt. 2011
 copied from here: http://arduino.cc/forum/index.php/topic,75334.0.html
 */
 
const int numberLEDs = 14;
int led[numberLEDs];
  
int RightSleeveLEDs[]={
  2,3,4,5,6,7,8,9,10,11,12,13,14,15}; //14
int LeftSleeveLEDs[]={
  4,5,6,7,8,9,10,11,12,13,14,15,16,17}; //14
int CollarLEDs[]={
  2,3,4,5,6,7,8,9,10,11,12,13,14,15}; //16
  


int r[] = {
  9,13,4,17,10,6,13,5,16,15,7,8,11,12};// random variable
int xIMUpin1 = 0;
int xIMUpin2 = 1;
int xIMUpin3 = 18; // = A4
// int xIMUpin4 = 19; // = A5

int value1, value2, value3;

int delayTime = 2; // can't be 0!
int delayTime1 = 1; // can't be 0!
int delayTime3 = 3; // can't be 0!


void setup(){

  Serial.begin(9600);

  for (int z=0;z<numberLEDs;z++){
//    pinMode(RightSleeveLEDs[z],OUTPUT);
    pinMode(LeftSleeveLEDs[z],OUTPUT);
//    pinMode(CollarLEDs[z],OUTPUT);
  } //for z


  pinMode(xIMUpin1, INPUT);
  digitalWrite(xIMUpin1, HIGH); // internal pullup for triggerpin
  pinMode(xIMUpin2, INPUT);
  digitalWrite(xIMUpin2, HIGH); // internal pullup for triggerpin
  pinMode(xIMUpin3, INPUT);
  digitalWrite(xIMUpin3, HIGH); // internal pullup for triggerpin
  
    // in order singles
  for(int i = 0; i<numberLEDs; i++){
    led[i] = Coll
    
    arLEDs[i];
    }
}





void loop(){

  // in order singles
  for(int i = 0; i<numberLEDs; i++){
    for(int x=1;x<254;x++) {
      spwm(x,led[i],delayTime1);
    }
    for(int x=254;x>1;x--) {
      spwm(x,led[i],delayTime1);
    }
  }
  
  
  
  // random singles
    for(int i = 0; i<numberLEDs; i++){
    for(int x=1;x<254;x++) {
      spwm(x,r[i],delayTime3);
    }
    for(int x=254;x>1;x--) {
      spwm(x,r[i],delayTime3);
    }
  }
  


// in order grouped

  for(int i = 0; i<numberLEDs; i++){
    for(int x=1;x<254;x++) {
      spwm(x,led[i],delayTime);
      spwm(x,led[i+1],delayTime);
      spwm(x,led[i+2],delayTime);
      spwm(x,led[i+3],delayTime);
      spwm(x,led[i+4],delayTime);
    }
    for(int x=254;x>1;x--) {
      spwm(x,led[i],delayTime);
      spwm(x,led[i+1],delayTime);
      spwm(x,led[i+2],delayTime);
      spwm(x,led[i+3],delayTime);
      spwm(x,led[i+4],delayTime);
    }
  }



  


// all on, all off
  for(int x=1;x<254;x++) {
    for(int i = 0; i<numberLEDs; i++){
      spwm(x,led[i],delayTime3);
    }
  }

  for(int x=254;x>1;x--) {
    for(int i = 0; i<numberLEDs; i++){
      spwm(x,led[i],delayTime3);
    }
  }

}


/*
  value1 = digitalRead(xIMUpin1);
 value2 = digitalRead(xIMUpin2);
 value3 = digitalRead(xIMUpin3);
 
 if(value1 == 1 && value2 == 1 && value3 == 1){
 for(int x=1;x<254;x++)  spwm(x,led[0],delayTime);
 for(int x=254;x>1;x--)  spwm(x,led[0],delayTime);
 }
 
 if(value1 == 0 && value2 == 1 && value3 == 1){
 for(int x=1;x<254;x++)  spwm(x,led[1],delayTime);
 for(int x=254;x>1;x--)  spwm(x,led[1],delayTime);
 }
 
 if(value1 == 1 && value2 == 0 && value3 == 1){
 for(int x=1;x<254;x++)  spwm(x,led[2],delayTime);
 for(int x=254;x>1;x--)  spwm(x,led[2],delayTime);
 }
 
 if(value1 == 1 && value2 == 1 && value3 == 0){
 for(int x=1;x<254;x++)  spwm(x,led[3],delayTime);
 for(int x=254;x>1;x--)  spwm(x,led[3],delayTime);
 }
 
 
 for(int i = 0; i<numberLEDs; i++){
 for(int x=1;x<254;x++)  spwm(x,led[i],delayTime);
 for(int x=254;x>1;x--)  spwm(x,led[i],delayTime);     
 }
 */


void spwm(int freq,int pin,int sp) {
  //on
  digitalWrite(pin,HIGH);
  delayMicroseconds(sp*freq);
  // off
  digitalWrite(pin,LOW);
  delayMicroseconds(sp*(255-freq));
} //spwm














