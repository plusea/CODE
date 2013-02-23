// modified version of tom igoe's Serial Graphing Sketch

import processing.serial.*;

Serial myPort;  // The serial port
PFont myFont;  // font for writing text to the window
boolean fontInitialized = false;  // whether the font's been initialized 
String state;
float xoff1 = 0.0; // for testing
float xoff2 = 0.1; // for testing
color rightColor = color(180,15,15);
color leftColor = color(220,180,10);
boolean smoothing = true;
Graph right = new Graph(rightColor, smoothing); 
Graph left = new Graph(leftColor, smoothing); 

void setup () {
  size(800,600);        
  println(Serial.list());
  //String portName = Serial.list()[#];
  //myPort = new Serial(this, myPort, 9600);
  //myPort = new Serial(this, "/dev/tty.usbmodem12341", 9600);
  //myPort.clear();

  myFont = createFont("HelveticaNeue-18.vlw", 14);
  textFont(myFont);
  fontInitialized = true;

  background(255);
  ellipseMode(CENTER);
  smooth();
  grid();
  
}

void draw () {
  // generate test value instead of serial port read
  xoff1 = xoff1 + .01;
  xoff2 = xoff2 + .01;
  float n = noise(xoff1) * width;

  float m = noise(xoff2) * height;
  int testValue1 = int(n);
  int testValue2 = int(m);
  
  right.peak(testValue1);
  left.peak(testValue2);
}

void grid(){
  for(int i=1; i<height; i+=50*height/1023){
    strokeWeight(0.5);
    stroke(0);
    line(0 , height-i , width , height-i);
  }
}

void keyPressed(){
  if (key==' ')
  saveFrame();
}
