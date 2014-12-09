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
int numberOfSensors = 16;  //6 for ArduIMU, up to 16 for xOSC
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
  //size(displayWidth, displayHeight);

  // initialise GloveData object:
  gloves = new GlovesData();

  // Serial stuff:
  println(Serial.list());
  String portName = Serial.list()[0];
  //myPort = new Serial(this, portName, 115200);

  // font stuff:
  fontA = loadFont("Helvetica-40.vlw");
  textAlign(CENTER);
  textFont(fontA, 14);  
  textAlign(LEFT);

  background(255);
  smooth();
  strokeWeight(5);
}


//==================================================
// draw function
void draw(){ 
  //graph();
  megaGraph();

}


//==================================================
void graph() {

  //--------------------------------------------  
  // -----------POSTURE RECOGNITION-------------
  //--------------------------------------------

  if(gloves.postureL == 0) {
    stroke(lightgreen);
    line(xpos, 0, xpos, height);
  }



  //--------------------------------------------  
  // -----------SENSOR GRAPHS-------------------
  //--------------------------------------------

  for (int i = 0; i < numberOfSensors; i++) {  // skip input 1 (0) because connected to xBIUM serial!
    float ypos = map(gloves.flexL[i], 0, 1, 0, height/numberOfSensors);
    // figure out the y position for this particular graph:
    float graphBottom = i * height/numberOfSensors;
    ypos = ypos + graphBottom;
 
    if(i < 8) stroke(purple);
    else stroke(orange);
    line(xpos, previousSensorValue[i], xpos+1, ypos);

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







  //--------------------------------------------  
  // -----------MEGA GLOVE GRAPH-------------------
  //--------------------------------------------
void megaGraph() {
  for (int i = 0; i < numberOfSensors; i++) {  // skip input 1 (0) because connected to xBIUM serial!
    float ypos = map(gloves.flexL[i], 0, 1, 0, height/numberOfSensors);
    // figure out the y position for this particular graph:
    float graphBottom = i * height/numberOfSensors;
    ypos = ypos + graphBottom;
 
    if(i < 8) stroke(purple);
    else stroke(orange);
    line(xpos, previousSensorValue[i], xpos+1, ypos);

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
  //if (key==' ')
  // saveFrame();

  gloves.setLeftLEDColour((int)random(0,254),(int)random(0,254),(int)random(0,254));
  gloves.pulseMotor();
  // gloves.setLeftLEDColour(100,100,100);
}




















