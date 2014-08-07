//===============================================================
//
// THE GLOVES PROJECT - PROCESSING BRIDGE
//
// Receives and displays all glove messages
// Adapt to use the gloves with your own code
//
// Requirements: the oscP5 library (http://www.sojamo.de/libraries/oscP5/)
//
//===============================================================

// create GlovesData object to interpret osc messages
GlovesData gloves;

import processing.serial.*;
PFont fontA;
float pxr;
float pyr;
float pxl;
float pyl;


Serial myPort;  // Create object from Serial class
//==================================================
// setup function
void setup() {
  size(1800, 1000);
  //size(displayWidth, displayHeight);

  // initialise GloveData object
  gloves = new GlovesData();
  //println(Serial.list());
  printArray(Serial.list());
  String portName = Serial.list()[11];
  //myPort = new Serial(this, portName, 115200);

  //noStroke();

  fontA = loadFont("Helvetica-40.vlw");
  textAlign(CENTER);
  // Set the font and its size (in units of pixels)
  textFont(fontA, 32);
  
  textAlign(LEFT);
}




//==================================================
// draw function
void draw(){  
  drawLeft();
  drawRight();
  //playBottles();
  //gloveValues();

  fill(250,250,250,1);
  noStroke();
  rect(0,0, width, height);
}



void playBottles() {
  float pan = map(gloves.yawL, -90, +90, 0, 180);
  myPort.write(int(pan));

  float flickThreshold = 0.5;
  if (gloves.flexL[1] < flickThreshold) {
    myPort.write(255);
    delay(100);
  }
}




void servoTest() {
  for (int i=0; i<180; i++) {
    myPort.write(i);
    delay(100);
  }
  myPort.write(255);
  for (int i=180; i>0; i--) {
    myPort.write(i);
    delay(300);
  }
}




void drawLeft() {
  float x = map(gloves.yawL, -60, 60, -(width/2), width/2);
  float y = map(gloves.pitchL, 40, -40, -(height/2), height/2);

  color brushcolor = color(0,0,0);

  float brushsize = map(gloves.rollL, 60, -60, 1,100);
  brushsize = constrain(brushsize, 1, 100);

  if(gloves.postureL == 1) background(255);  //if fist then clear canvas 
  if(gloves.postureL == 0) brushcolor = color(255,180,3);
  else if(gloves.postureL == 2) brushcolor = color(3,160,255);
  else if(gloves.postureL == 3) brushcolor = color(255,3,142);
  else brushcolor = color(0,0,0);
  //if(gloves.drumL == true) background(0);

  strokeWeight(brushsize);
  fill(brushcolor);
  stroke(brushcolor);

  line((width/2)+pxl, (height/2)+pyl, (width/2)+x, (height/2)+y);

  pxl = x;
  pyl = y;
}








void drawRight() {
  float x = map(gloves.yawR, -60, 60, -(width/2), width/2);
  float y = map(gloves.pitchR, 40, -40, -(height/2), height/2);

  color brushcolor = color(0,0,0);

  float brushsize = map(gloves.rollR, 60, -60, 1,100);
  brushsize = constrain(brushsize, 1, 100);

  if(gloves.postureR == 1) background(255);  //if fist then clear canvas 
  if(gloves.postureR == 0) brushcolor = color(255,180,3);
  else if(gloves.postureR == 2) brushcolor = color(3,160,255);
  else if(gloves.postureR == 3) brushcolor = color(255,3,142);
  else brushcolor = color(0,0,0);

  strokeWeight(brushsize);
  fill(brushcolor);
  stroke(brushcolor);

  line((width/2)+pxr, (height/2)+pyr, (width/2)+x, (height/2)+y);

  pxr = x;
  pyr = y;
}








void gloveValues()
{
  background(50);

  textSize(40);
  text("The Gloves ProjectProcessing Bridge", 20, 50);

  textSize(15);
  text("Click the screen to randomly change LED colours", 20, 80);

  int textLeft = 20;
  int textRight = 500;
  int valLeft = 250;
  int valRight = 730;

  textSize(25);

  // pitch
  text("pitchL: ", textLeft, 150);
  text(nfs(gloves.pitchL, 0, 2), valLeft, 150);
  text("pitchR: ", textRight, 150);
  text(nfs(gloves.pitchR, 0, 2), valRight, 150);


  // yaw
  text("yawL: ", textLeft, 190);
  text(nfs(gloves.yawL, 0, 2), valLeft, 190);
  text("yawR: ", textRight, 190);
  text(nfs(gloves.yawR, 0, 2), valRight, 190);

  // roll
  text("rollL: ", textLeft, 230);
  text(nfs(gloves.rollL, 0, 2), valLeft, 230);
  text("rollR: ", textRight, 230);
  text(nfs(gloves.rollR, 0, 2), valRight, 230);

  // average flex
  text("averageFlexL: ", textLeft, 270);
  text(nfs(gloves.averageFlexL, 0, 2), valLeft, 270);
  text("averageFlexR: ", textRight, 270);
  text(nfs(gloves.averageFlexR, 0, 2), valRight, 270);


  // drum hits
  text("drumL: ", textLeft, 310);
  text(gloves.drumRegionL, valLeft + 100, 310);
  text(nfs(gloves.drumIntensityL, 0, 2), valLeft + 150, 310);
  if (gloves.drumL)
  {
    gloves.drumL = false;
    fill(255);
  }
  else {
    noFill();
  };
  rect(valLeft, 310-20, 80, 20);


  text("drumR: ", textRight, 310);
  text(gloves.drumRegionR, valRight + 100, 310);
  text(nfs(gloves.drumIntensityR, 0, 2), valRight + 150, 310);
  if (gloves.drumR)
  {
    gloves.drumR = false;
    fill(255);
  }
  else {
    noFill();
  }
  rect(valRight, 310-20, 80, 20);


  // posture
  text("postureL: ", textLeft, 350);
  text(gloves.postureL, valLeft, 350);
  text("postureR: ", textRight, 350);
  text(gloves.postureR, valRight, 350);

  // direction
  text("directionL: ", textLeft, 390);
  text(gloves.directionL, valLeft, 390);
  text("directionR: ", textRight, 390);
  text(gloves.directionR, valRight, 390);


  // gyroPeak X
  text("gyroPeakXL: ", textLeft, 430);
  if (gloves.gyroPeakXL)
  {
    gloves.gyroPeakXL = false;
    fill(255);
  }
  else {
    noFill();
  };
  rect(valLeft, 430-20, 80, 20);


  text("gyroPeakXR: ", textRight, 430);
  if (gloves.gyroPeakXR)
  {
    gloves.gyroPeakXR = false;
    fill(255);
  }
  else {
    noFill();
  }
  rect(valRight, 430-20, 80, 20);


  // gyroPeak Y
  text("gyroPeakYL: ", textLeft, 470);
  if (gloves.gyroPeakYL)
  {
    gloves.gyroPeakYL = false;
    fill(255);
  }
  else {
    noFill();
  };
  rect(valLeft, 470-20, 80, 20);


  text("gyroPeakYR: ", textRight, 470);
  if (gloves.gyroPeakYR)
  {
    gloves.gyroPeakYR = false;
    fill(255);
  }
  else {
    noFill();
  }
  rect(valRight, 470-20, 80, 20);



  // gyroPeak Z
  text("gyroPeakZL: ", textLeft, 510);
  if (gloves.gyroPeakZL)
  {
    gloves.gyroPeakZL = false;
    fill(255);
  }
  else {
    noFill();
  };
  rect(valLeft, 510-20, 80, 20);


  text("gyroPeakZR: ", textRight, 510);
  if (gloves.gyroPeakZR)
  {
    gloves.gyroPeakZR = false;
    fill(255);
  }
  else {
    noFill();
  }
  rect(valRight, 510-20, 80, 20);


  // magnitude
  text("magnitudeL: ", textLeft, 550);
  text(nfs(gloves.magnitudeL, 0, 2), valLeft, 550);
  text("magnitudeR: ", textRight, 550);
  text(nfs(gloves.magnitudeR, 0, 2), valRight, 550);

  // flex for individual fingers
  text("flexL: ", textLeft, 590);
  textSize(17);
  for (int i = 0;i < 6;i++)
  {
    text(nfs(gloves.flexL[i], 0, 1), valLeft - 30 + (i*40), 590);
  }

  textSize(25);
  // flex for individual fingers
  text("flexR: ", textRight, 590);
  textSize(17);
  for (int i = 0;i < 6;i++)
  {
    text(nfs(gloves.flexR[i], 0, 1), valRight - 30 + (i*40), 590);
  }

  textSize(25);


  // wristAngle
  text("wristAngle: " + nfs(gloves.wristAngle, 0, 2), 360, 650);
}


// when the mouse is pressed
void mousePressed()
{
  // choose a random number
  int mode = int(random(4));

  // for various values of the number, choose two colours
  if (mode == 0)
  {
    gloves.setLeftLEDColour(255, 0, 0);
    gloves.setRightLEDColour(255, 0, 255);
  }

  if (mode == 1)
  {
    gloves.setLeftLEDColour(0, 255, 0);
    gloves.setRightLEDColour(255, 255, 0);
  }

  if (mode == 2)
  {
    gloves.setLeftLEDColour(0, 0, 255);
    gloves.setRightLEDColour(0, 255, 255);
  }

  if (mode == 3)
  {
    gloves.setLeftLEDColour(255, 0, 255);
    gloves.setRightLEDColour(0, 255, 0);
  }
}





