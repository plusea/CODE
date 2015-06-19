/*
*  By Hannah Perner-Wilson, www.plusea.at
*  Scroll down to set your thresholds!
*  press "g" to switch to graph and
*  press "d" to switch to draw mode
*/

import processing.serial.*;

// definition of window size
// you can change the size of the window as you like
// the thresholdGraph will be scaled to fit
// the optimal size for the thresholdGraph is 1000 x 400
int xWidth = 1000;
int yHeight = 700;

// xPos input array, using prefix
int[] xPosArr= {0,0}; 

// 
int[] messageArr= {0,0}; 
  
// Arrays for threshholding
int[] threshMax= {0,0}; 
int[] threshMin= {0,0}; 

// Array and variable for sorting out which is the largest value
int[] maxArray = {0,0};

// variables for serial connection. portname and baudrate are user specific
Serial port1;

//Set your serial port here (look at list printed when you run the application once)
String V3 = Serial.list()[0];
String portname1 = V3;
int baudrate = 9600;
  
int prefix = 1;
boolean myCatch = true;
int serialIN = 0;
int serialINPUT = 0; 
String buffer = ""; 
int value = 0; 
int state = 0;  // for toggling between clear draw and graph
float x = 0;
float y = 0;

// ThresholdGraph draws grid and poti states
ThresholdGraph in;

void setup(){
  // set size and framerate
  size(xWidth, yHeight);
  frameRate(25);
  background(255);
  strokeWeight(5);
  stroke(0);
  smooth();
  strokeCap(ROUND);
  
  PFont phFont;
  int phFontsize = 30;
  String fontname = "Monaco-14.vlw";
  String inputName = "";
  phFont = loadFont(fontname);
  textFont(phFont, phFontsize);

  // establish serial port connection      
  port1 = new Serial(this, portname1, baudrate);
  println(Serial.list());  // print serial list

  // create DisplayItems object
  in = new ThresholdGraph();
  
  // THRESHOLD VALUES:
  // using the thresholdGraph you can determine the MIN and MAX values
  // of your sensors. Enter these here. They must lie between 0 and 1000.
  
    //MIN trashhold
    threshMin[0] = 0;   // one
    threshMin[1] = 0;   // two
    
    //MAX trashhold
    threshMax[0] = 1000;   // one
    threshMax[1] = 1000;   // two
}//end setup




// draw listens to serial port, draw 
void draw(){
  
  // listen to serial port and trigger serial event  
  while(port1.available() > 0){
        serialIN = port1.read();
        serialEvent(serialIN);  
        }
        
  // threshold serial input
  threshHolding();  
  
  if(state == 0){
  // draw serial input
  in.update();
  }//end if(state)
  
  if(state == 1){
  // draw page
  background(255);
  
  // use analog input 1 for x position
  // use analog input 2 for x position
  x = (xWidth/255) * messageArr[0];
  y = (yHeight/255) * messageArr[1];

  fill(0);
  ellipseMode(CENTER);
  ellipse(x,y, 10,10);
  }//end if(state)
}//end draw()


void keyPressed(){
  if (key=='d')
    state = 1;
  if (key=='g')
    state = 0;
}
