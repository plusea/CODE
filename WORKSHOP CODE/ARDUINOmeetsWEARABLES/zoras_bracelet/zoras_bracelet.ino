/*
// code for a bracelet with 2 LEDs and 2 buttons
 // pressing button1 toggles between LED1, LED2, both and none
 // pressing button2 increases brightness of all LEDs
 */






//----------declare variables--------------
const int buttonPin1 = 2;    
const int buttonPin2 = 3;
const int ledPin1 =  9;      
const int ledPin2 = 10;
int buttonState1 = 0;
int buttonState2 = 0;
int fadeValue = 0;
int counter = 0;
boolean buttonPressed = false;
long lastDebounceTime = 0;  
long debounceDelay = 50;    
int lastButtonState = LOW;   






//----------setup--------------
void setup() {

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  // the following code sets the internal pull-up resistors for the two buttons. 
  // this way you don't need to add any external resistors!
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);  

  Serial.begin(9600);  // begin serial communication
}//end setup






//----------loop--------------
void loop(){

  //////////// CODE FOR BUTTON 1 (toggle) //////////////

  buttonState1 = digitalRead(buttonPin1);

  // use debounce to check that button was pressed properly.
  // if button2 is pressed, look at the time (millis) and remember (=store in variable)
  if (buttonState1 == LOW) {
    lastDebounceTime = millis();
  } 

  if ((millis() - lastDebounceTime) > debounceDelay) {
    buttonPressed = true;
  }

  if(buttonPressed == false){
    counter += 1;
  }


  //////////// CODE FOR BUTTON 2 (fade on) //////////////

  buttonState2 = digitalRead(buttonPin2);  // read state of button2

    if (buttonState2 == LOW) {     
    fadeValue += 2;  //how fast LED gets brighter
  } 

  if (counter == 0) {  // turn ON both LEDs
    analogWrite(ledPin1, fadeValue);
    analogWrite(ledPin2, fadeValue);
  }

  if (counter == 1) {    // only turn on LED1
    analogWrite(ledPin1, fadeValue);
  }

  if (counter == 2) {  // only turn on LED2
    analogWrite(ledPin2, fadeValue);
  }

  if(counter >= 3) {  // turn OFF both LEDs
    counter = 0;  // reset counter
    analogWrite(ledPin1, 0);
    analogWrite(ledPin2, 0);
  } 

  lastButtonState = buttonState2;  //remember last button state


  //////////// PRINT: //////////////
  // for debugging, print the counter value and fadevalue:
  Serial.print("counter: ");  
  Serial.print(counter);  
  Serial.print("\t fadeValue: "); 
  Serial.println(fadeValue);  

}//end loop



