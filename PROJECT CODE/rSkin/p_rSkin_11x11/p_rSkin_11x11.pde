import processing.serial.*;

int maxNumberOfSensors = 121;       // Arduino has 6 analog inputs, so I chose 6
int rows = 11;
int cols = 11;
int squareSize = 90;
int x=0;
int y=0;
float[] previousValue = new float[maxNumberOfSensors];  // array of previous values
Serial myPort;                    // The serial port
boolean fontInitialized = false;  // whether the font's been initialized
PFont myFont;                     // font for writing text to the window


void setup () {
  size(rows*squareSize, cols*squareSize);        
  println(Serial.list());
  String portName = Serial.list()[0];
  //myPort = new Serial(this, portName, 9600);
  myPort = new Serial(this, portName, 115200);
  myPort.clear();
  myPort.bufferUntil('\n');  // don't generate a serialEvent() until you get a newline (\n) byte

  // create a font with the fourth font available to the system:
  myFont = createFont(PFont.list()[3], 14);
  textFont(myFont);
  fontInitialized = true;

  background(255);    // set inital background
  smooth();  // turn on antialiasing
}

void draw () {
}

void keyPressed(){
  if (key==' ')
    saveFrame();
}

