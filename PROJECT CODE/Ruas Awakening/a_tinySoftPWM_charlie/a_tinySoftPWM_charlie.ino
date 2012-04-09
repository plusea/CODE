/*Software PWM on Attiny85
 Ernst Christensen 16.okt. 2011
 */

int led[]={
  0,1,2,3,0,1,2,3};
int numberLEDs = 4;
int delayTime = 12;
int testDelay = 250;


void setup(){
  for(int z=0;z<numberLEDs;z++) pinMode(led[z], OUTPUT);
  for(int z=0;z<numberLEDs;z++) digitalWrite(led[z], LOW);
  pinMode(4, INPUT);
}


void loop(){
  //testRun();
  testCharliePlex();
  //loopSoftPWM();
}



void loopSoftPWM() {
  for (int i=0; i<numberLEDs; i++){
    digitalWrite(led[i], HIGH);
    delayTime = random(2,15);

    for (int x=1;x<254;x++){
      spwm(x,led[i+1],delayTime);
      spwm(x,led[i+2],delayTime);
      spwm(x,led[i+3],delayTime);
    }    
    for (int x=254;x>1;x--){
      spwm(x,led[i+1],delayTime);
      spwm(x,led[i+2],delayTime);
      spwm(x,led[i+3],delayTime);
    }

  }
}


void testRun(){
  int count = 0;

  for(int i=0; i<12; i++){

    for (int y=0; y<numberLEDs; y++){
      pinMode(y, INPUT);
    }
    pinMode(count, OUTPUT);
    digitalWrite(count, LOW);
    delay(testDelay);

    if(count == 3) count = 0;
    
    count++;  
    
  }


}


void testCharliePlex(){
  
  // 1
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  digitalWrite(0, LOW);
    for (int x=1;x<254;x++) spwm(x,1,delayTime);
    for (int x=254;x>1;x--) spwm(x,1,delayTime);
  delay(testDelay);
  // 2
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  digitalWrite(0, LOW);
    for (int x=1;x<254;x++) {
      spwm(x,2,delayTime);
    }
    for (int x=254;x>1;x--) spwm(x,2,delayTime);
  delay(testDelay);
  // 3
  pinMode(0, OUTPUT);
  pinMode(1, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
  digitalWrite(0, LOW);
    for (int x=1;x<254;x++) spwm(x,3,delayTime);
    for (int x=254;x>1;x--) spwm(x,3,delayTime);
  delay(testDelay);
  // 4
  pinMode(0, OUTPUT);
  pinMode(1, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
  digitalWrite(1, LOW);
    for (int x=1;x<254;x++) spwm(x,0,delayTime);
    for (int x=254;x>1;x--) spwm(x,0,delayTime);
  delay(testDelay);
  // 5
  pinMode(0, OUTPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  digitalWrite(1, LOW);
    for (int x=1;x<254;x++) spwm(x,2,delayTime);
    for (int x=254;x>1;x--) spwm(x,2,delayTime);
  delay(testDelay);
  // 6
  pinMode(0, OUTPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  digitalWrite(1, LOW);
    for (int x=1;x<254;x++) spwm(x,3,delayTime);
    for (int x=254;x>1;x--) spwm(x,3,delayTime);
  delay(testDelay);
  // 7
  pinMode(0, INPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
  digitalWrite(2, LOW);
    for (int x=1;x<254;x++) spwm(x,0,delayTime);
    for (int x=254;x>1;x--) spwm(x,0,delayTime);
  delay(testDelay);
  // 8
  pinMode(0, INPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
  digitalWrite(2, LOW);
    for (int x=1;x<254;x++) spwm(x,1,delayTime);
    for (int x=254;x>1;x--) spwm(x,1,delayTime);
  delay(testDelay);
  // 9
  pinMode(0, INPUT);
  pinMode(1, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  digitalWrite(2, LOW);
    for (int x=1;x<254;x++) spwm(x,3,delayTime);
    for (int x=254;x>1;x--) spwm(x,3,delayTime);
  delay(testDelay);
  // 10
  pinMode(0, INPUT);
  pinMode(1, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
    for (int x=1;x<254;x++) spwm(x,0,delayTime);
    for (int x=254;x>1;x--) spwm(x,0,delayTime);
  delay(testDelay);
    // 11
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
    for (int x=1;x<254;x++) spwm(x,1,delayTime);
    for (int x=254;x>1;x--) spwm(x,1,delayTime);
  delay(testDelay);
    // 12
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
    for (int x=1;x<254;x++) spwm(x,2,delayTime);
    for (int x=254;x>1;x--) spwm(x,2,delayTime);
  delay(testDelay);
}

void spwm(int freq,int spin,int sp){

  //on
  digitalWrite(spin,HIGH);
  delayMicroseconds(sp*freq);

  // off
  digitalWrite(spin,LOW);
  delayMicroseconds(sp*(255-freq));


} //spwm










