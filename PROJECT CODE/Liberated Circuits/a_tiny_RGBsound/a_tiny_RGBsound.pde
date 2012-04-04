/*
code based on dave mellis's touch example
 >> 
 */

// RGB fade code for at tiny

int fadeTime = 2; // number of milli-seconds between colour fading

int rLEDPin = 1; // PWM
int gLEDPin = 0; // PWM
int bLEDPin = 2;
int speakerPin = 4;
int heatPin = 3;

int outputs[] = {
  0,1,2,3,4};

int blue;
float blueChance;


int rounds = 200;




void setup() {
  for(int i = 0; i < 5; i++){
    pinMode(outputs[i], OUTPUT);
  }
}





void loop() {
  for(int i=0; i < rounds; i++){
  analogWrite(rLEDPin, int(random(0,255)));
  analogWrite(gLEDPin, int(random(0,255)));
  blueChance = random(0,500);
  if(blueChance < 250) blue=1;
  else blue=0;
  digitalWrite(bLEDPin, blue);
  
  beep(speakerPin,random(50*i,12000),random(0,10));
    
  delay(random(0,rounds - i));
  }
  
  analogWrite(rLEDPin, 0);
  analogWrite(gLEDPin, 0);
  digitalWrite(bLEDPin, 0);
  
  digitalWrite(heatPin, HIGH);
  delay(7000);
  
  //digitalWrite(bLEDPin, 50);
  
  digitalWrite(heatPin, LOW);
  delay(10000);
}





void fadeRGB(){
  controlledFade(255,0,0, 0,255,0); //red to green
  controlledFade(0,255,0, 0,0,255); //green to blue
  controlledFade(0,0,255, 255,0,0); // blue to red
}



void controlledFade(int r1,int g1,int b1, int r2,int g2,int b2){
  int red1 = r1;
  int green1 = g1;
  int blue1 = b1;
  int red2 = r2;
  int green2 = g2;
  int blue2 = b2;

  float redDifference = 255.0 / (red1 - red2);
  float greenDifference = 255.0 / (green1 - green2);
  float blueDifference = 255.0 / (blue1 - blue2);

  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue++) {
    float rValue = red1 - fadeValue/redDifference;
    float gValue = green1 - fadeValue/greenDifference;
    float bValue = blue1 - fadeValue/blueDifference;

    analogWrite(rLEDPin, rValue);
    analogWrite(gLEDPin, gValue);
    analogWrite(bLEDPin, bValue);
    delay(fadeTime);
  }
}


void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds)     // the sound producing function
{ 	 
  int x; 	 

  long delayAmount = (long)(1000000/frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
  for (x=0;x<loopTime;x++) 	 
  { 	 
    digitalWrite(speakerPin,HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(speakerPin,LOW);
    delayMicroseconds(delayAmount);
  } 	 
} 	 

void scale ()
{ 	 
    int duration=10;
  beep(speakerPin,2093,duration); 	//C: play the note C (C7 from the chart linked to above) for 500ms
  beep(speakerPin,2349,duration); 	//D
  beep(speakerPin,2637,duration); 	//E
  beep(speakerPin,2793,duration); 	//F
  beep(speakerPin,3136,duration); 	//G
  beep(speakerPin,3520,duration); 	//A
  beep(speakerPin,3951,duration); 	//B
  beep(speakerPin,4186,duration); 	//C
}

