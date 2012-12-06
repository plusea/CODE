/*
Penguin visualization code >> http://www.plusea.at/?p=2378
 */

import processing.serial.*;
Serial penguinPort;
PFont penguinFont;  // font for writing text to the window
int scaleValue = 50;
float leftWing, rightWing, squeezeAmount, tiltDirection, Ax, Ay, Az;
color where;

void setup(){
  size(1200, 600); 

  //////////// SERIAL PORT ///////////
  println(Serial.list());  // prints a list of the serial ports
  penguinPort = new Serial(this, "/dev/tty.RN42-E59C-SPP", 115200);  ///// BLUETOOTH /////  
  //penguinPort = new Serial(this, "/dev/cu.RN42-E59C-SPP", 115200);  ///// BLUETOOTH /////
  //penguinPort = new Serial(this, "/dev/tty.usbserial-A900fwsd", 9600);  ///// FTDI /////
  penguinPort.clear();
  penguinPort.bufferUntil('\n');  // don't generate a serialEvent() until you get a newline (\n) byte

  // FONT //
  penguinFont = loadFont("AmericanTypewriter-Bold-48.vlw");
  textFont(penguinFont, 48);  // Set the font and its size (in units of pixels)
  background(255); 
  stroke(200,0,0);
  fill(0);
  strokeWeight(1);
  smooth(); 

}

void draw(){
  background(255);
  rectMode(CORNER);
  fill(0);
  rect(0,0, width/2, height);

  fill(255);
  text("RECEIVE", 50,50);

  fill(0);
  text("SEND", width/2+50,50);


  // INPUT
  pushMatrix();
  rectMode(CENTER);
  translate(width/8, height/3);
  scale(scaleValue);
  strokeWeight(0);
  fill(255);
  stroke(0);

  if(tiltDirection == 1) fill(200,0,0);
  else fill(255);
  rect(2,0,1,1);  // up

  if(tiltDirection == 2) fill(200,0,0);
  else fill(255);
  rect(2,4,1,1);  // down

  if(tiltDirection == 4) fill(200,0,0);
  else fill(255);
  rect(4,2,rightWing+1,rightWing+1);  // right

  if(tiltDirection == 3) fill(200,0,0);
  else fill(255);
  rect(0,2,leftWing+1,leftWing+1);  // left  

  ellipseMode(CENTER);
  fill(squeezeAmount*75,0,0);  // squeeze
  ellipse(2,2, squeezeAmount, squeezeAmount);
  popMatrix();



  // OUTPUT 
  pushMatrix();
  rectMode(CORNER);
  translate(4.6*width/8, height/3);
  scale(scaleValue);
  strokeWeight(0);
  fill(0);
  stroke(0);



  fill(200,0,0);
  rect(0,0,1,1);  // red
  fill(0,200,0);
  rect(2,0,1,1);  // green
  fill(0,0,200);
  rect(4,0,1,1);  // blue
  fill(255);
  rect(6,0,0.5,1);  // white
  fill(0);
  rect(6.5,0,0.5,1);  // off

  fill(200);
  rect(0,2,1,1);  // quiet 
  fill(150);
  rect(2,2,1,1);  // moderate
  fill(5);
  rect(4,2,1,1);  // loud
  fill(245);
  rect(6,2,1,1);  // off

  fill(210);
  rect(0,4,1,1);  // low
  fill(160);
  rect(2,4,1,1);  // medium
  fill(10);
  rect(4,4,1,1);  // high
  fill(250);
  rect(6,4,1,1);  // off
  popMatrix();  
} 




void mouseClicked() {
  where = get(mouseX, mouseY);
  println(where);


  // LIGHT
  if(where == -3670016) {
    println('r');
    penguinPort.write('r');
  }

  if(where == -16726016) {
    println('g');
    penguinPort.write('g');
  }

  if(where == -16777016) {
    println('b');
    penguinPort.write('b');
  }

  if(where == -1) {
    println('w');
    penguinPort.write('w');
  }

  if(where == -16777216) {
    println('z');
    penguinPort.write('z');
  }


  // SOUND
  if(where == -3618616) {
    println('q');
    penguinPort.write('q');
  }

  if(where == -6908266) {
    println('m');
    penguinPort.write('m');
  }

  if(where == -16448251) {
    println('l');
    penguinPort.write('l');
  }

  if(where == -657931) {
    println('n');
    penguinPort.write('n');
  }


  // VIBRATION
  if(where == -2960686) {
    println('t');
    penguinPort.write('t');
  }

  if(where == -6250336) {
    println('y');
    penguinPort.write('v');
  }

  if(where == -16119286) {
    println('h');
    penguinPort.write('h');
  }

  if(where == -328966) {
    println('s');
    penguinPort.write('s');
  }

}

