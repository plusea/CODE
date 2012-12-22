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
int windowWidth = 1200;
int windowHeight = 800;
int textBoxHeight = 60;

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
  leftPort = new Serial(this, "/dev/tty.RN42-059C-SPP", 115200);  ///// BLUETOOTH /////
  //leftPort = new Serial(this, "/dev/tty.usbserial-A6007x5s", 9600);  ///// FTDI /////
  leftPort.clear();
  leftPort.bufferUntil('\n');  // don't generate a serialEvent() until you get a newline (\n) byte

  //////// RIGHT ////////
  rightPort = new Serial(this, "/dev/tty.RN42-0592-SPP", 115200);  ///// BLUETOOTH /////
  //rightPort = new Serial(this, "/dev/tty.usbserial-A700ewYh", 9600);  ///// FTDI /////
  rightPort.clear();
  rightPort.bufferUntil('\n');  // don't generate a serialEvent() until you get a newline (\n) byte
  
  ////////////     FONT    ///////////
  myFont = loadFont("HelveticaNeue-18.vlw");
  textFont(myFont, 18);  // Set the font and its size (in units of pixels)
  fontInitialized = true;
}

////////////////////////////////////
////////////     DRAW    ///////////
////////////////////////////////////
void draw() {
  strokeWeight(5);
  stroke(200,0,0);
  line(xpos, previousRightValue - textBoxHeight, xpos+1, rightPSmap - textBoxHeight);
  previousRightValue = rightPSmap;
  stroke(0,0,200);
  line(xpos, previousLeftValue - textBoxHeight, xpos+1, leftPSmap - textBoxHeight);
  previousLeftValue = leftPSmap;
  if (xpos >= width) { // if you've drawn to the edge of the window, start at the beginning again
    saveFrame();  // save a screen-shot of the application window
    xpos = 0;
    background(255);
  } 
  else xpos+=1;  // change the increment of x to control the speed of graphing incoming values
  if (fontInitialized) {
    fill(215);
    noStroke();
    rect(0, windowHeight-textBoxHeight, windowWidth, windowHeight);
    fill(200,0,0);
    text("Impact: " + int(rightPS), windowWidth/2 + 10, windowHeight - 42);
    text(" X: " + rightX, 3*windowWidth/4 + 10, windowHeight - 42);
    text(" Y: " + rightY, 3*windowWidth/4 + 10, windowHeight - 22);
    text(" Z: " + rightZ, 3*windowWidth/4 + 10, windowHeight - 2);
    fill(0,0,200);
    text("Impact: " + int(leftPS), 10, windowHeight - 42);
    text(" X: " + leftX, windowWidth/4 + 10, windowHeight - 42);
    text(" Y: " + leftY, windowWidth/4 + 10, windowHeight - 22);
    text(" Z: " + leftZ, windowWidth/4 + 10, windowHeight - 2);
  }
}
