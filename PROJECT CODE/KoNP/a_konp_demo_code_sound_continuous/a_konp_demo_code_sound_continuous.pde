// code for sound and led output on an ATtiny85
// using leah buechley's sound code, taken from: http://web.media.mit.edu/~leah/LilyPad/07_sound_code.html

int sensorPin = 2;
int speakerPin = 3;
int LED0 = 0;
int LED1 = 1;
int LED2 = 2;

int reading;
int count = 0;
int threshold = 850;

int LEDstate = 0;
int SENSORstate = 0;
int previousSENSORstate = 0;
int SENSORgo = 0;

void setup()
{
  pinMode(sensorPin, INPUT);
  digitalWrite(4, HIGH);//sensorPin
  pinMode(speakerPin, OUTPUT);
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED0, HIGH);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
}

void loop() {
  reading = analogRead(sensorPin);
  SENSORstate = reading/(threshold/8);

  if(SENSORstate == previousSENSORstate) SENSORgo = 0;
  else SENSORgo = 1;

  if(SENSORstate == 0 && SENSORgo == 1) scale('C');
  if(SENSORstate == 1 && SENSORgo == 1) scale('D');
  if(SENSORstate == 2 && SENSORgo == 1) scale('E');
  if(SENSORstate == 3 && SENSORgo == 1) scale('F');
  if(SENSORstate == 4 && SENSORgo == 1) scale('G');
  if(SENSORstate == 5 && SENSORgo == 1) scale('A');
  if(SENSORstate == 6 && SENSORgo == 1) scale('B');
  if(SENSORstate == 7 && SENSORgo == 1) scale('H');

  previousSENSORstate = SENSORstate;

  if(reading < threshold && LEDstate == 0){
    count++;
    LEDstate=1;
  }
  if(count == 1 && LEDstate == 1) {
    digitalWrite(LED0, HIGH);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  }
  if(count == 2  && LEDstate == 1) {
    digitalWrite(LED0, LOW);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
  }
  if(count == 3  && LEDstate == 1) {
    digitalWrite(LED0, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
  }
  if(count == 4  && LEDstate == 1) {
    digitalWrite(LED0, HIGH);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
  }
  if(count > 4) count = 1;
  if(reading > threshold) LEDstate = 0;  
}



void scale (char note)
{ 	 
  if(note == 'C')
    beep(speakerPin,2093,500); 	//C: play the note C (C7 from the chart linked to above) for 500ms
  if(note == 'D')
    beep(speakerPin,2349,500); 	//D
  if(note == 'E')
    beep(speakerPin,2637,500); 	//E
  if(note == 'F')
    beep(speakerPin,2793,500); 	//F
  if(note == 'G')
    beep(speakerPin,3136,500); 	//G
  if(note == 'A')
    beep(speakerPin,3520,500); 	//A
  if(note == 'B')
    beep(speakerPin,3951,500); 	//B
  if(note == 'H')
    beep(speakerPin,4186,500); 	//C  
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
    //break;
  } 	 
  SENSORgo = 0;
} 		  
