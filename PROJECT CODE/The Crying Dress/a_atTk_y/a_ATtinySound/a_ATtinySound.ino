/*
 * LilyPad tutorial: sound
 *
 * Uses a LilyPad speaker module to produce simple musical notes
 * For a chart of the frequencies of different notes see:
 * http://www.phy.mtu.edu/~suits/notefreqs.html
 */

int waterPin = 3; 	// LED is connected to digital pin 13
int speakerPin = 4; 	// speaker connected to digital pin 9
int waterResistance = 0;

void setup() 	 
{ 	 
  pinMode(waterPin, INPUT); 	// sets the ledPin to be an output
  pinMode(speakerPin, OUTPUT); 	// sets the speakerPin to be an output
  digitalWrite(3, HIGH);
} 	 

void loop() {	// run over and over again
  waterResistance = analogRead(waterPin);
  if(waterResistance < 900){
    waterResistance = map(waterResistance, 0, 900, 0,200);
    //beep(speakerPin, waterResistance, 100); 
    for(int i=0; i<2000; i+=1){
      beep(speakerPin, i, 10); 
    }
        for(int i=2000; i>0000; i-=1){
      beep(speakerPin, i, 10); 
    }
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



