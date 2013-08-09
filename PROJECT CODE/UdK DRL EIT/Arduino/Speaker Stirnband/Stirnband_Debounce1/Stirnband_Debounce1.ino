/* 
 Speaker Stirnband code that tracks button (earflap) presses and depending on number
 of presses, changes melody that is playing
 */


const int buttonPin = 4;
const int speakerPin = 3;
const int ledPin =  13;
int ledState = HIGH;         // the current state of the output pin
int buttonReading;           // incoming values from pushbutton pin
int previousButtonReading;
int buttonCounter;             // the number of button presses
int lastButtonReading = LOW;   // the previous reading from the input pin
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers



void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  //  digitalWrite(buttonPin, HIGH);
  pinMode(ledPin, OUTPUT);

  // for debugging:
  Serial.begin(9600);
}



void loop() {
  buttonReading = digitalRead(buttonPin);
  Serial.print("buttonReading: ");
 Serial.println(buttonReading);
 
  if (buttonReading == LOW) buttonPressed();  // if button was pressed, run buttonPressed function
}


void buttonPressed(){


  
  if (previousButtonReading == HIGH && (millis() - lastDebounceTime) > debounceDelay) {
    buttonCounter++;  //increase buttonstate counter to keep track of number of button presses
   lastDebounceTime = millis();
    if(buttonCounter >= 2) buttonCounter = 0;
  }

  //if(buttonCounter == 0) playMelody0();
  //else if(buttonCounter == 1) playMelody1();
  //else if(buttonCounter == 2) {}

  // set the LED using the state of the button:
  digitalWrite(ledPin, buttonCounter);

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonReading:
  lastButtonReading = buttonReading;
}


void playMelody0(){
  beep(speakerPin, 1000, 500);
  beep(speakerPin, 2000, 500);
  beep(speakerPin, 3000, 500);
}


void playMelody1(){
  beep(speakerPin, 5000, 500);
  beep(speakerPin, 6000, 500);
  beep(speakerPin, 7000, 500);
}



