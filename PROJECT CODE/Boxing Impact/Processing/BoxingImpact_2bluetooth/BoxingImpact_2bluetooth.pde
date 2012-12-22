/* 
 this code is for a pair of boxing impact gloves, and is taken from the "many serial ports" processing example as well as tom igoe's arduino graph code.
 the code runs on your computer, receiving a stream of serial data from a bluetooth mate module attached to an arduino mini pro.
 before running the application, pair your computer with the bluetooth modules, enter the generic passcode "1234".
 more documentation: http://www.plusea.at/?p=2291
 */

import processing.serial.*;

Serial rightPort, leftPort;
PFont myFont;  // font for writing text to the window
boolean fontInitialized = false;  // whether the font's been initialized
int xpos;
int leftPS;
float leftPSmap;
float previousLeftValue;
int leftX;  // accelerometer
int leftY;
int leftZ; 
int rightPS; 
float rightPSmap; 
float previousRightValue;
int rightX;
int rightY;
int rightZ;
int windowWidth = 1800;
int windowHeight = 1000;
int textBoxHeight = 60;
int leftThresholdValue = 300;
int rightThresholdValue = 300;

////////////////////////////////////
////////////    SETUP    ///////////
////////////////////////////////////
void setup()  {
  size(windowWidth, windowHeight);  //size of application window
  background(255);    // set inital background
  smooth();  // turn on antialiasing

  //////////// SERIAL PORT ///////////
  println(Serial.list());  // prints a list of the serial ports

  //////// LEFT ////////
  leftPort = new Serial(this, "/dev/tty.00-06-66-43-05-9c-SPP", 115200);  ///// BLUETOOTH /////
  //leftPort = new Serial(this, "/dev/tty.usbserial-A6007x5s", 9600);  ///// FTDI /////
  leftPort.clear();
  leftPort.bufferUntil('\n');  // don't generate a serialEvent() until you get a newline (\n) byte

  //////// RIGHT ////////
 
  //rightPort = new Serial(this, "/dev/tty.usbserial-A700ewYh", 9600);  ///// FTDI /////
  rightPort.clear();
  rightPort.bufferUntil('\n');  // don't generate a serialEvent() until you get a newline (\n) byte
  
  ////////////     FONT    ///////////
  myFont = loadFont("HelveticaNeue-18.vlw");
  textFont(myFont, 18);  // Set the font and its size (in units of pixels)
  fontInitialized = true;
  
  grid();
}

////////////////////////////////////
////////////     DRAW    ///////////
////////////////////////////////////
void draw() {
  strokeWeight(4);
  stroke(240,45,15);
  line(xpos, previousRightValue, xpos+1, rightPSmap);
  previousRightValue = rightPSmap;
  
  stroke(240,170,15);
  line(xpos, previousLeftValue, xpos+1, leftPSmap);
  previousLeftValue = leftPSmap;
  
  if (xpos >= width) { // if you've drawn to the edge of the window, start at the beginning again
    saveFrame();  // save a screen-shot of the application window
    xpos = 0;
    background(255);
    grid();
  } 
  else xpos+=1;  // change the increment of x to control the speed of graphing incoming values
  
  if (fontInitialized) {
    fill(215);
    noStroke();
    rect(0, windowHeight-textBoxHeight, windowWidth, windowHeight);
    fill(240,45,15);
    text("Impact: " + int(rightPS), windowWidth/2 + 10, windowHeight - 42);
    text(" X: " + rightX, 3*windowWidth/4 + 10, windowHeight - 42);
    text(" Y: " + rightY, 3*windowWidth/4 + 10, windowHeight - 22);
    text(" Z: " + rightZ, 3*windowWidth/4 + 10, windowHeight - 2);
    fill(240,170,15);
    text("Impact: " + int(leftPS), 10, windowHeight - 42);
    text(" X: " + leftX, windowWidth/4 + 10, windowHeight - 42);
    text(" Y: " + leftY, windowWidth/4 + 10, windowHeight - 22);
    text(" Z: " + leftZ, windowWidth/4 + 10, windowHeight - 2);
  }
}

void grid(){
  for(int i=1; i<windowHeight-textBoxHeight; i+=(windowHeight-textBoxHeight)/10){
    strokeWeight(0.5);
    line(0 , i , windowWidth , i);
  }
}
