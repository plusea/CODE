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

  // set a variable to track when the button is actually pressed
  if(buttonState == LOW) {
    buttonPressed = true;
  }
  // detect the event of the button going from pressed to not pressed,
  // and increment the mode when this is detected
  if(buttonPressed == true && buttonState == HIGH) {
    buttonPressed = false;
    mode = mode + 1;
      Serial.println(mode);
  }

}







