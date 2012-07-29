/*
 Example code for the Embroidery gone Electronic workshop 2012.
 >> http://www.kobakant.at/DIY/?p=3444
 ATtiny45 with one analog input mapped to 4 different outputs:
    * piano: play different notes depending on analog input value
    * noise: modulate frequency depending on analog input value
    * notes: play a different note when contact is made or button is pressed
    * melody: play a pre-set melody when contact is made or button is pressed
 */

#define noisePin 3 
#define noiseSensor 3
#define pianoPin 4  
#define pianoSensor 2
#define togglePin 2  
#define melodyPin 1
#define speakerPin 0

//turn speaker on and off:
#define speakerOn() PORTB = 0b00000001
#define speakerOff() PORTB = 0b00000000

// timer interrupt variables:
unsigned int flip = 0;
unsigned int latency;
unsigned int tcnt;  
unsigned int turn = 1; 
unsigned int count = 0;
boolean toggle = false;
int noiseValue = 0;
int pianoValue = 0;
int toggleValue = 0;
int melodyValue = 0;
int frequency = 10000;

int threshold = 800;
int previousNoiseValue; 
int delayAmmount = 1000;

int SENSORstate = 0;
int previousSENSORstate = 0;
int SENSORgo = 0;


void setup() { 	 
  pinMode(speakerPin, OUTPUT); 
  pinMode(noisePin, INPUT_PULLUP);
  pinMode(pianoPin, INPUT_PULLUP);
  pinMode(togglePin, INPUT_PULLUP);
  pinMode(melodyPin, INPUT_PULLUP);
} 	 


void loop() { 	
  toggleValue = digitalRead(togglePin); 
  melodyValue = digitalRead(melodyPin);
  noiseValue = analogRead(noiseSensor);
  pianoValue = analogRead(pianoSensor);


  // TOGGLE //////////////////////////////////////////////////////////
  if(toggleValue == 0){
    if(toggle == false) {
      count++;
      if(count > 7) count = 0;
      toggle = true;
    }
    play(speakerPin, 500 + (count * 700), 500);
  } // end if()
  else toggle = false;


  // MELODY //////////////////////////////////////////////////////////
  if(melodyValue == 0){
    unsigned int melodyDuration = 1000;
    play(speakerPin,2093,melodyDuration); 	//C: play the note C (C7 from the chart linked to above) for 500ms
    play(speakerPin,2349,melodyDuration); 	//D
    play(speakerPin,2637,melodyDuration); 	//E
    play(speakerPin,2793,melodyDuration); 	//F
    play(speakerPin,3136,melodyDuration); 	//G
    play(speakerPin,3520,melodyDuration); 	//A
    play(speakerPin,3951,melodyDuration); 	//B
    play(speakerPin,4186,melodyDuration); 	//C
  }


  // PIANO //////////////////////////////////////////////////////////
  if(pianoValue < threshold) {

    unsigned int SENSORstate = pianoValue/(threshold/8);
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
  }



  // NOISE //////////////////////////////////////////////////////////
  if(noiseValue < threshold) play(speakerPin, 800*((noiseValue+20)/20), 0);
  
}  // end loop



void scale (char note)
{ 	 
  int dur = 1000;
  if(note == 'C')
    play(speakerPin,2093,dur); 	//C: play the note C (C7 from the chart linked to above) for 500ms
  if(note == 'D')
    play(speakerPin,2349,dur); 	//D
  if(note == 'E')
    play(speakerPin,2637,dur); 	//E
  if(note == 'F')
    play(speakerPin,2793,dur); 	//F
  if(note == 'G')
    play(speakerPin,3136,dur); 	//G
  if(note == 'A')
    play(speakerPin,3520,dur); 	//A
  if(note == 'B')
    play(speakerPin,3951,dur); 	//B
  if(note == 'H')
    play(speakerPin,4186,dur); 	//C  
} 



void play(int pin, unsigned int freq, int duration){
  float halfT = 1000000.f / ((float)freq * 2.f);

  if(duration != 0){
    for(int x=0;x<duration;x++) 	 {
      digitalWrite(speakerPin, HIGH); //speakerOn();
      delayMicroseconds(halfT);
      digitalWrite(speakerPin, LOW); //speakerOff();
      delayMicroseconds(halfT);  
    }
  }
  else {
    digitalWrite(speakerPin, HIGH); //speakerOn();
    delayMicroseconds(halfT);
    digitalWrite(speakerPin, LOW); //speakerOff();
    delayMicroseconds(halfT); 
  }
}
