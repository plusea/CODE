/* 
 this code is for a pair of boxing impact gloves, and is taken from the "many serial ports" processing example as well as tom igoe's arduino graph code.
 the code runs on your computer, receiving a stream of serial data from a bluetooth mate module attached to an arduino mini pro.
 before running the application, pair your computer with the bluetooth modules, enter the generic passcode "1234".
 more documentation: http://www.plusea.at/?p=2291
 */

import processing.serial.*;

// SERIAL VARIABLES
Serial rightPort, leftPort;

// FONT VARIABLES
PFont myFont;  // font for writing text to the window
boolean fontInitialized = false;  // whether the font's been initialized
int leftSensor, rightSensor;

// LEFT VARIABLES
color leftColor = color(220,180,10);
int leftPS;
float mappedLeftPS;
float previousLeftPS;
int savedLeftXpos;
int leftX;  // accelerometer
int leftY;
int leftZ; 
int leftPeaks;
Boolean leftPeak = false;
float leftMaxim;
float savedLeftMaxim;
int leftThreshold = 300;

// RIGHT VARIABLES
color rightColor = color(180,15,15);
int rightPS; 
float mappedRightPS; 
float previousRightPS;
int savedRightXpos;
int rightX;
int rightY;
int rightZ;
int rightPeaks;
Boolean rightPeak = false;
float rightMaxim;
float savedRightMaxim;
int rightThreshold = 500;

// COUNTDOWN VARIABLES
int time = 1; // variable to keep track of time for three-minute countdown
int countDownSeconds = 180;
int xpos;
int speed = 1;

////////////////////////////////////
////////////    SETUP    ///////////
////////////////////////////////////
void setup()  {
  size(800, 600);  //size of application window
  background(255);    // set inital background
  smooth();  // turn on antialiasing

  //////////// SERIAL PORT ///////////
  println(Serial.list());  // prints a list of the serial ports


  //////// RIGHT ////////
  rightPort = new Serial(this,"/dev/cu.usbserial-A600f6Tn", 9600);  ///// FTDI /////
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
  strokeWeight(2);

  mappedLeftPS = map(leftPS, 0, 1023, height,0); // map the incoming sensor number to the window height
  mappedRightPS = map(rightPS, 0, 1023, height,0); // map the incoming sensor number to the window height

  // LEFT
  // if incoming value is above the threshold then keep track of highest values:
  if(leftPS > leftThreshold){  
    leftPeak = true;
    if(leftPS > leftMaxim) leftMaxim = leftPS;
  }

  // if incoming sensor value goes bellow threshold then register peak as highest stored value:
  if(leftPS < leftThreshold && leftPeak == true){  
    leftPeaks++;
    stroke(leftColor);
    fill(0);
    ellipse(xpos, map(leftMaxim,0,1023,height,0), 10, 10); // draw circle at peak to confirm correct detection
    text(leftMaxim, xpos, map(leftMaxim,0,1023,height,0));
    stroke(0);
    strokeWeight(4);
    line(xpos, map(leftMaxim,0,1023,height,0), savedRightXpos, savedRightMaxim);
    println("Left Maxim: " + leftMaxim);
    savedLeftXpos = xpos;
    savedLeftMaxim = map(leftMaxim,0,1023,height,0);
    leftMaxim = 0;
    leftPeak = false;
  }

  // RIGHT
  // if incoming value is above the threshold then keep track of highest values:
  if(rightPS > rightThreshold){  
    rightPeak = true;
    if(rightPS > rightMaxim) rightMaxim = rightPS;
  }

  // if incoming sensor value goes bellow threshold then register peak as highest stored value:
  if(rightPS < rightThreshold && rightPeak == true){  
    rightPeaks++;
    stroke(rightColor);
    fill(0);
    ellipse(xpos, map(rightMaxim,0,1023,height,0), 10, 10); // draw circle at peak to confirm correct detection
    text(rightMaxim, xpos, map(rightMaxim,0,1023,height,0));
    stroke(0);
    strokeWeight(4);
    line(xpos, map(rightMaxim,0,1023,height,0), savedLeftXpos, savedLeftMaxim);
    println("Right Maxim: " + rightMaxim);
    savedRightXpos = xpos;
    savedRightMaxim = map(rightMaxim,0,1023,height,0);
    rightMaxim = 0;
    rightPeak = false;
  }

  strokeWeight(2);
  stroke(leftColor);
  line(xpos, previousLeftPS, xpos+1, mappedLeftPS);
  stroke(rightColor);
  line(xpos, previousRightPS, xpos+1, mappedRightPS);

  previousLeftPS = mappedLeftPS;
  previousRightPS = mappedRightPS;

  if (xpos >= width) {  // if you've drawn to the edge of the window, start at the beginning again
    saveFrame();
    xpos = 0;
    background(255);
    grid();
    savedLeftXpos=0;
    savedRightXpos=0;
  }
  else xpos+=speed;




  // text at bottom of screen prints incoming impact value from pressure sensor 
  // and x,y,z values from accelerometer
  // LEFT
  fill(255);
  stroke(0);
  rect(5, height-75, 250, 70);
  fill(leftColor);
  text("Impact: " + leftPS, 10, height - 50);
  text("Peaks: " + leftPeaks, 10, height - 30);
  text(" X: " + leftX, 150, height - 50);
  text(" Y: " + leftY, 150, height - 30);
  text(" Z: " + leftZ, 150, height - 10);

  // RIGHT
  fill(255);
  stroke(0);
  rect(width-255, height-75, 250, 70);
  fill(rightColor);
  text("Impact: " + rightPS, width-250 + 10, height - 50);
  text("Peaks: " + rightPeaks, width-250 + 10, height - 30);
  text(" X: " + rightX, width-250 + 150, height - 50);
  text(" Y: " + rightY, width-250 + 150, height - 30);
  text(" Z: " + rightZ, width-250 + 150, height - 10);


  // countdown text in top right corner
  fill(255);
  stroke(0);
  rect(width-55, 5, 50, 25);
  fill(0);
  text(time*countDownSeconds - millis() / 1000, width-50, 25);
  if((millis()/1000) / (time*countDownSeconds) == 1) time++;



}



void keyPressed(){
  if (key==' ') saveFrame();
  if (key=='r'){
    leftPeaks = 0;
    rightPeaks = 0;
  }
}


void grid(){
  background(255);
  for(int i=1; i<height; i+=height/10){
    strokeWeight(0.5);
    line(0 , i , width , i);
  }
}







