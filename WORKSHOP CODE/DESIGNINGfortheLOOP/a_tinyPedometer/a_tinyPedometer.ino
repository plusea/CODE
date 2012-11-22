/*
Reads analog input from one pin and every time the input goes bellow a set threshold 
 it counts one and displays the increase in count on a 7-segment LED display
 */


int count = 0;
int charliePin;
int sensorValue = 0;
int itteration = 0;



void setup(){
  for (int pin=0;pin<4;pin++){
    pinMode(pin,OUTPUT);
  }

  pinMode(4,INPUT);
  digitalWrite(4, HIGH);
}



void loop(){
  //sensorValue = analogRead(2);
  //if(sensorValue < threshold) count++;

  testLoop();
}




// blink through all 12 LEDs:
void testLoop(){
    for (int c=1;c<13;c++) {
      charliePlexPin(c);
      delay(100);
  }
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
    digitalWrite(0, LOW);
    digitalWrite(1, HIGH);
    break;

    // 2
  case 2:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    digitalWrite(0, LOW);
    digitalWrite(2, HIGH);
    break;

    // 3
  case 3:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    digitalWrite(0, LOW);
    digitalWrite(3, HIGH);
    break;

    // 4
  case 4:
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    digitalWrite(1, LOW);
    digitalWrite(0, HIGH);
    break;

    // 5
  case 5:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    digitalWrite(1, LOW);
    digitalWrite(2, HIGH);
    break;

    // 6
  case 6:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    digitalWrite(1, LOW);
    digitalWrite(3, HIGH);
    break;

    // 7
  case 7:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    digitalWrite(2, LOW);
    digitalWrite(0, LOW);
    break;

    // 8
  case 8:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    digitalWrite(2, LOW);
    digitalWrite(1, HIGH);
    break;

    // 9
  case 9:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    break;

    // 10
  case 10:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    digitalWrite(3, LOW);
    digitalWrite(0, HIGH);
    break;

    // 11
  case 11:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    digitalWrite(3, LOW);
    digitalWrite(1, HIGH);
    break;

    // 12
  case 12:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    digitalWrite(3, LOW);
    digitalWrite(2, HIGH);
    break;
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


