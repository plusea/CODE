const int leftButtonPin = 2;     // the number of the pushbutton 1 pin
const int rightButtonPin = 3;     // the number of the pushbutton 2 pin
const int led1Pin =  5;      // the number of the LED pin
const int led2Pin =  6;      // the number of the LED pin
const int led3Pin =  7;      // the number of the LED pin
const int led4Pin =  8;      // the number of the LED pin
const int led5Pin =  9;      // the number of the LED pin

int leftButtonPressed = 0;  // stores the state of the button (0=not pressed, 1=pressed)
int rightButtonPressed = 0;  // stores the state of the button (0=not pressed, 1=pressed)

//variables to keep track of the current state of the buttons
int leftButtonState = 0;
int rightButtonState = 0;

//variables to keep track of the previous state of the buttons
int leftButtonLastState = 0; 
int rightButtonLastState = 0; 

//variable to count how many times both the buttons are pushed
int bothPushCounter = 0;
int leftPushCounter = 0;
int rightPushCounter = 0;

//variables for the frames
int looplength = 800;
int framecount = 8;
int framelength;
int frame = 0;
unsigned long time = 0; // used to store the current time in milliseconds
unsigned long longPress = 0; // used to store the current time in milliseconds

int hack = 0;
int doubleHack = 0;
void setup() {
  // initialize the LED pin as an output:
  pinMode(led1Pin, OUTPUT);      
  pinMode(led2Pin, OUTPUT);      
  pinMode(led3Pin, OUTPUT);      
  pinMode(led4Pin, OUTPUT);      
  pinMode(led5Pin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(leftButtonPin, INPUT);     
  pinMode(rightButtonPin, INPUT);
  //initialize Serial to port 9600     
  Serial.begin(9600);
  //initialize the frame length
  framelength = looplength / framecount;  
}

void loop(){
  // read the state of the pushbutton value:
  leftButtonState = digitalRead(leftButtonPin);
  rightButtonState = digitalRead(rightButtonPin);

  if(leftButtonState == LOW) {
    leftButtonPressed = true;
  }

  if(rightButtonState == LOW) {
    rightButtonPressed = true;
  }

  // ----------- determine which button combinations are pressed! ----------------
  // LEFT:
  if(leftButtonPressed == true && leftButtonState == HIGH) {
    leftButtonPressed = false;
    hack = 2;
  }
  // RIGHT:
  else if(rightButtonPressed == true && rightButtonState == HIGH) {
    rightButtonPressed = false;
    hack = 3;
  }
  // BOTH:
  else if(leftButtonPressed == true && leftButtonState == HIGH && rightButtonPressed == true && rightButtonState == HIGH) {
    int timeStamp = millis();
    if(millis() - timeStamp > 1000) hack = 0;
        hack = 1;
    leftButtonPressed = false;
    rightButtonPressed = false;

  }

  //set the frame:
  time = millis();
  frame = (time % looplength) / framelength; 

  switch(hack) {
    //-------------- all off -------------------
  case 0:
    digitalWrite(led1Pin, LOW);
    digitalWrite(led2Pin, LOW);
    digitalWrite(led3Pin, LOW);
    digitalWrite(led4Pin, LOW);
    digitalWrite(led5Pin, LOW);
    break;
    //-------------- all on -------------------
  case 1:
    digitalWrite(led1Pin, HIGH);
    digitalWrite(led2Pin, HIGH);
    digitalWrite(led3Pin, HIGH);
    digitalWrite(led4Pin, HIGH);
    digitalWrite(led5Pin, HIGH);
    break;
    //-------------- left -------------------
  case 2:
    switch(frame) {
      digitalWrite(led1Pin, LOW); 
      digitalWrite(led2Pin, LOW); 
      digitalWrite(led3Pin, LOW); 
      digitalWrite(led4Pin, LOW); 
      digitalWrite(led5Pin, HIGH); 
      break;
    case 1:
      digitalWrite(led1Pin, LOW); 
      digitalWrite(led2Pin, LOW); 
      digitalWrite(led3Pin, LOW); 
      digitalWrite(led4Pin, HIGH); 
      digitalWrite(led5Pin, LOW); 
      break;
    case 2:
      digitalWrite(led1Pin, LOW); 
      digitalWrite(led2Pin, LOW); 
      digitalWrite(led3Pin, HIGH); 
      digitalWrite(led4Pin, LOW); 
      digitalWrite(led5Pin, LOW); 
      break;
    case 3:
      digitalWrite(led1Pin, LOW); 
      digitalWrite(led2Pin, HIGH); 
      digitalWrite(led3Pin, LOW); 
      digitalWrite(led4Pin, LOW); 
      digitalWrite(led5Pin, LOW); 
      break;
    case 4:
      digitalWrite(led1Pin, HIGH); 
      digitalWrite(led2Pin, LOW); 
      digitalWrite(led3Pin, LOW); 
      digitalWrite(led4Pin, LOW); 
      digitalWrite(led5Pin, LOW); 
      break;
    }
    //-------------- right -------------------
  case 3:
    switch(frame) {
    case 0:
      digitalWrite(led1Pin, HIGH); 
      digitalWrite(led2Pin, LOW); 
      digitalWrite(led3Pin, LOW); 
      digitalWrite(led4Pin, LOW); 
      digitalWrite(led5Pin, LOW); 
      break;
    case 1:
      digitalWrite(led1Pin, LOW); 
      digitalWrite(led2Pin, HIGH); 
      digitalWrite(led3Pin, LOW); 
      digitalWrite(led4Pin, LOW); 
      digitalWrite(led5Pin, LOW); 
      break;
    case 2:
      digitalWrite(led1Pin, LOW); 
      digitalWrite(led2Pin, LOW); 
      digitalWrite(led3Pin, HIGH); 
      digitalWrite(led4Pin, LOW); 
      digitalWrite(led5Pin, LOW); 
      break;
    case 3:
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
  }
  //-------------------------------------------



  rightButtonLastState = rightButtonState;
  leftButtonLastState = leftButtonState;


}


