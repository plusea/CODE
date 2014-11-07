//===============================================================
//
// THE GLOVES PROJECT - PROCESSING GRAPH for GESTURE RECOGNITION
// Receives and displays glove messages
// Requirements: the oscP5 library (http://www.sojamo.de/libraries/oscP5/)
//
//===============================================================

// create GlovesData object to interpret osc messages
GlovesData gloves;
import processing.serial.*;
Serial myPort;  // Create object from Serial class
PFont fontA;
int numberOfSensors = 6;  //6 for ArduIMU, up to 16 for xOSC
float[] previousSensorValue = new float[numberOfSensors];  // array of previous values
float xpos = 0;                     // x position of the graph
color orange = color(250, 115, 0);
color yellow = color(225, 205, 5);
color lightgreen = color(181, 275, 2);
color lightblue = color(53, 186, 237);
color darkblue = color(51, 112, 240);
color purple = color(189, 51, 240);
color pink = color(255, 0, 98);


//==================================================
// setup function
void setup() {
  size(1400, 1000);

  // initialise GloveData object:
  gloves = new GlovesData();

  // Serial stuff:
  //println(Serial.list());
  printArray(Serial.list());
  String portName = Serial.list()[0];
  //myPort = new Serial(this, portName, 115200);

  // font stuff:
  fontA = loadFont("Helvetica-40.vlw");
  textAlign(CENTER);
  textFont(fontA, 14);  
  textAlign(LEFT);

  background(255);
  smooth();
  strokeWeight(1);
}


//==================================================
// draw function
void draw(){ 
  graph();

}


//==================================================
void graph() {

  //--------------------------------------------  
  // -----------POSTURE RECOGNITION-------------
  //--------------------------------------------

  if(gloves.postureL == 0) {
    stroke(yellow);
    line(xpos, 0, xpos, height);
  }

  if(gloves.postureL == 1) {
    stroke(orange);
    line(xpos, 0, xpos, height);
  }

  if(gloves.postureL == 2) {
    stroke(lightgreen);
    line(xpos, 0, xpos, height);
  }

  if(gloves.postureL == 3) {
    stroke(lightblue);
    line(xpos, 0, xpos, height);
  }

  if(gloves.postureL == 4) {
    stroke(purple);
    line(xpos, 0, xpos, height);
  }

  if(gloves.postureL == 5) {
    stroke(pink);
    line(xpos, 0, xpos, height);
  }


  //--------------------------------------------  
  // -----------SENSOR GRAPHS-------------------
  //--------------------------------------------

  for (int i = 0; i < numberOfSensors; i++) {
    float ypos = map(gloves.flexL[i], 0, 1, 0, height/numberOfSensors);
    // figure out the y position for this particular graph:
    float graphBottom = i * height/numberOfSensors;
    ypos = ypos + graphBottom;


    /*
    // make a black block to erase the previous text:
     noStroke();
     fill(200);
     rect(10, graphBottom+1, 200, 20);
     
     // print the sensor numbers to the screen:
     fill(0);
     int textPos = int(graphBottom) + 14;
     text("Sensor " + i + ":" + gloves.flexL[i], 10, textPos);
     */

    // change colors to draw the graph line:
    //stroke(255, 64*i, 32*i);
    stroke(0);
    line(xpos, height-previousSensorValue[i], xpos+1, height-ypos);

    // save the current value to be the next time's previous value:
    previousSensorValue[i] = ypos;
  }

  if (xpos >= width) {
    saveFrame();
    xpos = 0;
    background(255);
  } 
  else {
    xpos+=1;
  }
}



//==================================================
void posture() {
  if(gloves.postureR == 1) {
    fill(200,0,0);
    rect(xpos, 0, xpos+5, height);
  }
}

//==================================================

void keyPressed(){
  if (key==' ')
    saveFrame();
}


















