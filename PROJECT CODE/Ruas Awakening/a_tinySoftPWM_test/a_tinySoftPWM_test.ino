/*Software PWM on Attiny85
Ernst Christensen 16.okt. 2011
copied from here: http://arduino.cc/forum/index.php/topic,75334.0.html
*/

int led[]={
  0,1,2,3,4};
  int mappedPin[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
int delayTime = 6;
int r = 0;
int y = 0;
int charliePin;


void setup(){
  for (int z=0;z<5;z++){
    pinMode(led[z],OUTPUT);
  } //for z
}



void loop(){
  testLoop();
}




// blink through all 12 LEDs:
void testLoop(){
  for (int i=0;i<20;i++) {
    for (int x=1;x<254;x++) spwm(x,mappedPin[i],delayTime);
    for (int x=254;x>1;x--) spwm(x,mappedPin[i],delayTime);
  }
}






// software PWM
void spwm(int freq,int pin,int sp){
  // call charlieplexing to set correct pin outs:
  charliePlexPin(pin);
  //on:
  digitalWrite(charliePin,HIGH);
  delayMicroseconds(sp*freq);
  // off:
  digitalWrite(charliePin,LOW);
  delayMicroseconds(sp*(255-freq));
}



// charlieplexing sets correct pin outs and returns pin to spwm to:
void charliePlexPin(int myLed){
  switch(myLed){

    // 1
  case 1:
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    digitalWrite(0, LOW);
    charliePin = 1;
    break;

    // 2
  case 2:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    digitalWrite(0, LOW);
    charliePin = 2;
    break;

    // 3
  case 3:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, INPUT);
    digitalWrite(0, LOW);
    charliePin = 3;
    break;

    // 4
  case 4:
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    digitalWrite(1, LOW);
    charliePin = 0;
    break;

    // 5
  case 5:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    digitalWrite(1, LOW);
    charliePin = 2;
    break;

    // 6
  case 6:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, INPUT);
    digitalWrite(1, LOW);
    charliePin = 3;
    break;

    // 7
  case 7:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    digitalWrite(2, LOW);
    charliePin = 0;
    break;

    // 8
  case 8:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    digitalWrite(2, LOW);
    charliePin = 1;
    break;

    // 9
  case 9:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, INPUT);
    digitalWrite(2, LOW);
    charliePin = 3;
    break;

    // 10
  case 10:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, INPUT);
    digitalWrite(3, LOW);
    charliePin = 0;
    break;

    // 11
  case 11:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, INPUT);
    digitalWrite(3, LOW);
    charliePin = 1;
    break;

    // 12
  case 12:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, INPUT);
    digitalWrite(3, LOW);
    charliePin = 2;
    break;
    
        // 12
  case 13:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
    charliePin = 0;
    break;
    
        // 12
  case 14:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, OUTPUT);
    digitalWrite(0, LOW);
    charliePin = 4;
    break;
    
        // 12
  case 15:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
    charliePin = 1;
    break;
    
        // 12
  case 16:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, OUTPUT);
    digitalWrite(1, LOW);
    charliePin = 4;
    break;
    
      case 17:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
    charliePin = 2;
    break;
    
      case 18:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    pinMode(4, OUTPUT);
    digitalWrite(2, LOW);
    charliePin = 4;
    break;
    
      case 19:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
    charliePin = 3;
    break;
    
      case 20:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(3, LOW);
    charliePin = 4;
    break;
  }
}
