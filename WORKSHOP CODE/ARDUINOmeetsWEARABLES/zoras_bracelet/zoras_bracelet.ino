// code for a bracelet with 2 LEDs and 2 buttons
// pressing button1 fades all LEDs on
// releasing button1 leaves LEDs at fade state
// pressing button2 toggles between LED1, LED2, both and none


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

 
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);  
  Serial.begin(9600);
}


//----------loop--------------
void loop(){
  
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);

Serial.println(counter);


 if (buttonState2 == LOW) {
    
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    
    buttonPressed = true;
  }
  
  if(buttonPressed == false){
  counter += 1;
  }



  if (buttonState1 == LOW) {     
    fadeValue += 5;
  } 



  if (counter == 0) {  
    analogWrite(ledPin1, fadeValue);
    analogWrite(ledPin2, fadeValue);
  }

  if (counter == 1) {  
    analogWrite(ledPin1, fadeValue);
  }

  if (counter == 2) {
    analogWrite(ledPin2, fadeValue);
  }

  if(counter >= 3) {  
    counter = 0;
    fadeValue = 0;
  } 

lastButtonState = buttonState2;

}
