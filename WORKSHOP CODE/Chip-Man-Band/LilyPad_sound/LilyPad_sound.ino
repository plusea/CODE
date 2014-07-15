/*
 * LilyPad tutorial: sound
 *
 * Uses a LilyPad speaker module to produce simple musical notes
 * For a chart of the frequencies of different notes see:
 * http://www.phy.mtu.edu/~suits/notefreqs.html
 */
 
int ledPin = 13; 	// LED is connected to digital pin 13
int speakerPin = 9; 	// speaker connected to digital pin 9
  	 
void setup() 	 
{ 	 
         pinMode(ledPin, OUTPUT); 	// sets the ledPin to be an output
         pinMode(speakerPin, OUTPUT); 	// sets the speakerPin to be an output
} 	 
  	 
void loop() 	// run over and over again
{ 	 
          scale(); 	// call the scale() function
          delay(1000); 	// delay for 1 second
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
          digitalWrite(ledPin,HIGH); 	//turn on the LED
          beep(speakerPin,2093,500); 	//C: play the note C (C7 from the chart linked to above) for 500ms
          beep(speakerPin,2349,500); 	//D
          beep(speakerPin,2637,500); 	//E
          beep(speakerPin,2793,500); 	//F
          beep(speakerPin,3136,500); 	//G
          beep(speakerPin,3520,500); 	//A
          beep(speakerPin,3951,500); 	//B
          beep(speakerPin,4186,500); 	//C
          digitalWrite(ledPin,LOW); 	//turn off the LED
} 
