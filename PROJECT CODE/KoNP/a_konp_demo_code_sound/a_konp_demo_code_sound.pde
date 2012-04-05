int sensorPin = 2;
int speakerPin = 3;
int LED0 = 0;
int LED1 = 1;
int LED2 = 2;

int count = 0;
int state = 0;
int reading;
int once = 0;
int threshold = 850;

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

void loop()
{
  reading = analogRead(sensorPin);
  if(reading < threshold && state == 0){
    count++;
    state=1;
  }

  if(count == 1 && state == 1) {
    digitalWrite(LED0, HIGH);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    scale('C');
  }

  if(count == 2  && state == 1) {
    digitalWrite(LED0, LOW);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    scale('D');
  }

  if(count == 3  && state == 1) {
    digitalWrite(LED0, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    scale('E');
  }

  if(count == 4  && state == 1) {
    digitalWrite(LED0, HIGH);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    scale('F');
  }

  if(count > 4) count = 1;

  if(reading > threshold) state = 0;   

  delay(10);
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
  if(note == 'C')
    beep(speakerPin,3520,500); 	//A
  if(note == 'A')
    beep(speakerPin,3951,500); 	//B
  if(note == 'CC')
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
    break;
  } 	 


} 		  













