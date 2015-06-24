/* taken from Stefan's Bike Light */

int buttonPin = 2;    // the number of the pushbutton pin

int buttonState = 0;    // variable for reading the button status
int buttonPressed = 0;  // stores the state of the button (0=not pressed, 1=pressed)
int mode = 0;           // mode will store the current blinking mode (0 - 3)

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  Serial.println(mode);

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
    // all LEDs off
    digitalWrite(led1Pin, LOW); 
    digitalWrite(led2Pin, LOW); 
    digitalWrite(led3Pin, LOW); 
    digitalWrite(led4Pin, LOW); 
    digitalWrite(led5Pin, LOW); 
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







