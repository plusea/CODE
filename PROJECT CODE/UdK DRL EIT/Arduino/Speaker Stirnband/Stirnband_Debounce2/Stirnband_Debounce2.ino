/* 
 Speaker Stirnband code that tracks button (earflap) presses and depending on number
 of presses, changes melody that is playing
 */
 
//pins:
int buttonPin = 4;
int speakerPin1 = 3;
int speakerPin2 = 2;
int ledPin = 1;

//variables:
int state = HIGH;      // the current state of the output pin
int reading;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin
int counter;
long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers



void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(speakerPin1, OUTPUT);
  pinMode(speakerPin2, OUTPUT);
  // for debugging:
  //Serial.begin(9600);
  beep(2000, 1000);  //beep to test speaker works
}



void loop()
{
  readingButton();
  if(counter == 0) playMelody0();
  if(counter == 1) playMelody1();
  if(counter == 2) playMelody2();
  if(counter == 3) playMelody3();
}



void readingButton(){
  reading = digitalRead(buttonPin);
  if (reading == LOW) buttonPressed();
  previous = reading;
}




void buttonPressed(){
  if (reading == LOW && previous == HIGH && millis() - time > debounce) {
    if (state == HIGH)
      state = LOW;
    else
      state = HIGH;
    time = millis();    
    counter++;
    if(counter >= 4) counter = 0;
    //Serial.println(counter);
  }
  digitalWrite(ledPin, state);
}





