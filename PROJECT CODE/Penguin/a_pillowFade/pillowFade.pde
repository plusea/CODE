int LEDs[] = {3,5,6,9,10,11};
int brightness;
int fadeAmount = 5
;

void setup()  { 
for(int i = 0; i < 6; i++){
  pinMode(LEDs[i], OUTPUT);
}
} 

void loop()  {
  
for(int i = 0; i < 6; i++){ 
  analogWrite(LEDs[i], brightness);    
}

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade: 
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ; 
  }     
  // wait for 30 milliseconds to see the dimming effect    
  delay(30);                            
}
