void beep (int frequencyInHertz, long timeInMilliseconds)     // the sound producing function
{ 	 
  int x; 	 
  long delayAmount = (long)(1000000/frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
  for (x=0;x<loopTime;x++) 	 
  { 	 
    //digitalWrite(speakerPin,HIGH);
    digitalWrite(speakerPin1,HIGH);
    digitalWrite(speakerPin2,HIGH);
    delayMicroseconds(delayAmount);
    //digitalWrite(speakerPin,LOW);
    digitalWrite(speakerPin1,LOW);
    digitalWrite(speakerPin2,LOW);
    delayMicroseconds(delayAmount);


  } 

  // even when playing melody, check if button has been pressed
  readingButton();
} 


