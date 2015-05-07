/* Stefan's Bike Light */

int buttonPin = 13;    // the number of the pushbutton pin
int led1Pin =  3;      // the number of the LED pin
int led2Pin =  5;      // the number of the LED pin
int led3Pin =  6;      // the number of the LED pin
int led4Pin =  9;      // the number of the LED pin
int led5Pin =  10;      // the number of the LED pin
int bright = 100;
int buttonState = 0;    // variable for reading the button status
int buttonPressed = 0;  // stores the state of the button (0=not pressed, 1=pressed)
int mode = 0;           // mode will store the current blinking mode (0 - 3)
int looplength = 600;  // how long the animation loop will take in milliseconds
int framecount = 8;     // number of frames in the animation
int framelength;        // number of milliseconds per FRAME (based on above 2 values)
unsigned long time = 0; // used to store the current time in milliseconds
int frame = 0;          // used to store the current animation frame (0 - framecount)

void setup() {
  // initialize the LED pins as an output:
  pinMode(led1Pin, OUTPUT);      
  pinMode(led2Pin, OUTPUT);      
  pinMode(led3Pin, OUTPUT);      
  pinMode(led4Pin, OUTPUT);      
  pinMode(led5Pin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  framelength = looplength / framecount;  
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // set a variable to track when the button is actually pressed
  if(buttonState == LOW) {
    buttonPressed = true;
  }
  // detect the event of the button going from pressed to not pressed,
  // and increment the mode when this is detected
  if(buttonPressed == true && buttonState == HIGH) {
    buttonPressed = false;
    mode = mode + 1;
  }

  // get the current time
  // and determine current animation frame from the current time
  // length of  animation and # of frames is declared at top of program
  time = millis();
  frame = (time % looplength) / framelength;

  // turn LEDs on and off based on mode and animation frame:
  switch(mode) {
    // -----------------------------------------------
  case 0:
    // all LEDs fade
    for(int i=0; i<255; i++){
      analogWrite(led1Pin, i); 
      analogWrite(led2Pin, i); 
      analogWrite(led3Pin, i); 
      analogWrite(led4Pin, i); 
      analogWrite(led5Pin, i); 
      delay(10);
    }
    for(int i=255; i>0; i--){
      analogWrite(led1Pin, i); 
      analogWrite(led2Pin, i); 
      analogWrite(led3Pin, i); 
      analogWrite(led4Pin, i); 
      analogWrite(led5Pin, i); 
      delay(10);
    }
    break;  

    // -----------------------------------------------
  case 1:
    // all LEDs on
    digitalWrite(led1Pin, HIGH); 
    digitalWrite(led2Pin, HIGH); 
    digitalWrite(led3Pin, HIGH); 
    digitalWrite(led4Pin, HIGH); 
    digitalWrite(led5Pin, HIGH); 
    break;  

    // -----------------------------------------------
  case 2:
    // alternating blinking
    switch(frame) {
    case 0:
    case 1:
    case 4:
    case 5:
      digitalWrite(led1Pin, HIGH); 
      digitalWrite(led2Pin, LOW); 
      digitalWrite(led3Pin, HIGH); 
      digitalWrite(led4Pin, LOW); 
      digitalWrite(led5Pin, HIGH); 
      break;
    case 2:
    case 3:
    case 6:
    case 7:
      digitalWrite(led1Pin, LOW); 
      digitalWrite(led2Pin, HIGH); 
      digitalWrite(led3Pin, LOW); 
      digitalWrite(led4Pin, HIGH); 
      digitalWrite(led5Pin, LOW); 
      break;
    }
    break;

    // -----------------------------------------------
  case 3:
    // back-and-forth "Knight Rider" pattern
    switch(frame) {
    case 0:
      digitalWrite(led1Pin, HIGH); 
      digitalWrite(led2Pin, LOW); 
      digitalWrite(led3Pin, LOW); 
      digitalWrite(led4Pin, LOW); 
      digitalWrite(led5Pin, LOW); 
      break;
    case 1:
    case 7:
      digitalWrite(led1Pin, LOW); 
      digitalWrite(led2Pin, HIGH); 
      digitalWrite(led3Pin, LOW); 
      digitalWrite(led4Pin, LOW); 
      digitalWrite(led5Pin, LOW); 
      break;
    case 2:
    case 6:
      digitalWrite(led1Pin, LOW); 
      digitalWrite(led2Pin, LOW); 
      digitalWrite(led3Pin, HIGH); 
      digitalWrite(led4Pin, LOW); 
      digitalWrite(led5Pin, LOW); 
      break;
    case 3:
    case 5:
      digitalWrite(led1Pin, LOW); 
      digitalWrite(led2Pin, LOW); 
      digitalWrite(led3Pin, LOW); 
      digitalWrite(led4Pin, HIGH); 
      digitalWrite(led5Pin, LOW); 
      break;
    case 4:
      digitalWrite(led1Pin, LOW); 
      digitalWrite(led2Pin, LOW); 
      digitalWrite(led3Pin, LOW); 
      digitalWrite(led4Pin, LOW); 
      digitalWrite(led5Pin, HIGH); 
      break;
    }
    break;

    // -----------------------------------------------
  default:
    // Go directly back to mode 0
    mode = 0;
    break;
  }
}








