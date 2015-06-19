/*
This code runs on the ATtiny85 microcontroller and is part of the Liberated Circuits project:
>> http://www.plusea.at/
 */

int fadeTime = 2; // number of milli-seconds between colour fading

int LEDPin0 = 0;
int LEDPin1 = 1;
int LEDPin2 = 2;
int LEDPin3 = 3;

int heatPin = 4;

int outputs[] = {
  0,1,2,3,4};

int rounds = 200;
float random0, random1, random2, random3;
int zero, one, two, three;

void setup() {
  for(int i = 0; i < 5; i++){
    pinMode(outputs[i], OUTPUT);
  }
}





void loop() {
  for(int i=0; i < rounds; i++){
    random0 = random(500);
    if(random0 < 250) zero=1;
    else zero=0;

    random1 = random(500);
    if(random1 < 250) one=1;
    else one=0;

    random2 = random(500);
    if(random2 < 250) two=1;
    else two=0;

    random3 = random(500);
    if(random3 < 250) three=1;
    else three=0;



    digitalWrite(LEDPin0, zero);
    digitalWrite(LEDPin1, one);
    digitalWrite(LEDPin2, two);
    digitalWrite(LEDPin3, three);

    delay(random(0,rounds - i));
  }

  digitalWrite(LEDPin0, 0);
  digitalWrite(LEDPin1, 0);
  digitalWrite(LEDPin2, 0);
  digitalWrite(LEDPin3, 0);

  digitalWrite(heatPin, HIGH);
  delay(7000);

  //digitalWrite(bLEDPin, 50);

  digitalWrite(heatPin, LOW);
  delay(60000);
}
