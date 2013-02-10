int redLEDPin = 3;
int greenLEDPin = 5;
int blueLEDPin = 6;
int whiteLEDPin = 9;

int blueGreen[] = {0, 255, 255};
int blue[] = {0, 0, 255};
int redOrange[] = {255, 255, 0};
int greenYellow[] = {127, 255, 0};
int jungleBackgroundColor[] = {60, 224, 27};
int dragonBackgroundColor[] = {242, 51, 150};
int underwaterBackgroundColor[] = {120, 212, 240};
int white[] = {255, 255, 255};
int deepBlueBackgroundColor[] = {37, 51, 207};
int sunlightBackgroundColor[] = {252, 196, 106};

void setup() {
pinMode(redLEDPin, OUTPUT);
pinMode(greenLEDPin, OUTPUT);
pinMode(blueLEDPin, OUTPUT);
pinMode(whiteLEDPin, OUTPUT);
  
}

void setColor(int* color) {
  analogWrite(redLEDPin, color[0]);
  analogWrite(greenLEDPin, color[1]);
  analogWrite(blueLEDPin, color[2]);
  
  
}

void setWhiteLEDLevel (int level) {
  analogWrite(whiteLEDPin, level);
}
void setColor(int r, int g, int b) {
  analogWrite(redLEDPin, r);
  analogWrite(greenLEDPin, g);
  analogWrite(blueLEDPin, b);
}

void loop() {

setWhiteLEDLevel(255);
setColor(white);
delay(5000);
setColor(jungleBackgroundColor);
delay(5000);
setColor(dragonBackgroundColor);
delay(5000);
//setColor(underwaterBackgroundColor);
//delay(5000);
setColor(deepBlueBackgroundColor);
delay(5000);

setColor(sunlightBackgroundColor);
delay(5000);



//setColor(blueGreen);
//delay(5000);
//setColor(blue);
//delay(5000);
//setColor(redOrange);
//delay(5000);
//setColor(greenYellow);
//delay(5000);
}
