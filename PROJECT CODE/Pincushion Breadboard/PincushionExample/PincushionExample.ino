#define r 0
#define g 1
#define y 2
#define delayTime 6

void setup() {                
  pinMode(r, OUTPUT);     
  pinMode(g, OUTPUT);     
  pinMode(y, OUTPUT);  
  digitalWrite(r, LOW);
  digitalWrite(g, LOW);
  digitalWrite(y, LOW);  
}

void loop() {
  for (int x=1;x<254;x++) spwm(x,r,delayTime);
  for (int x=254;x>1;x--) spwm(x,r,delayTime);
  
    for (int x=1;x<254;x++) spwm(x,g,delayTime);
  for (int x=254;x>1;x--) spwm(x,g,delayTime);
  
    for (int x=1;x<254;x++) spwm(x,y,delayTime);
  for (int x=254;x>1;x--) spwm(x,y,delayTime);
  //digitalWrite(r, LOW);
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

