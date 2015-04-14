import oscP5.*;
import netP5.*;
import ddf.minim.*;

OscP5 oscP5;
NetAddress myRemoteLocation;
Minim minim;
AudioSample kick;
AudioSample snare;
AudioSample bass;
AudioSample cymbal;
AudioSample hihat;
AudioSample kick2;

// global puppeteer variables:
int roll;

float RightRoll_value;
float RightPitch_value;
float RightIndexFlex_value;
float RightMiddleFlex_value;
float RightRingFlex_value;

float LeftButtonPress_value;
float LeftRoll_value;
float LeftPitch_value;
float LeftIndexFlex_value;
float LeftMiddleFlex_value;
float LeftRingFlex_value;

float LeftFistYaw_value;
float x, y;

float angleRhip = 0.0;
float angleRknee = 0.0;
float angleRshoulder = 0.0;
float angleRelbow = 0.0;

float angleLhip = 0.0;
float angleLknee = 0.0;
float angleLshoulder = 0.0;
float angleLelbow = 0.0;

float segLength = 100;

void setup() {
  size(500, 500);
  // start oscP5, telling it to listen for incoming messages at port 5001 */
  oscP5 = new OscP5(this, 9000);
  // set the remote location to be the localhost on port 5001
  myRemoteLocation = new NetAddress("127.0.0.1", 9000);

  //size(displayWidth, displayHeight);
  stroke(0, 160);
  x = width * 0.5;
  y = height * 0.5;
  
  minim = new Minim(this);
  kick = minim.loadSample( "BD.mp3", 512);
  snare = minim.loadSample("SD.wav", 512);
  bass = minim.loadSample("bass_single.wav", 512);
  cymbal = minim.loadSample("cymbal_single.wav", 512);
  hihat = minim.loadSample("hihat_single.wav", 512);
  kick2 = minim.loadSample("kick_single.wav", 512);
  
  kick2.trigger();
}
void draw()
{
  background(255);
  sound();
//  float changeTransparent = LeftFistYaw_value;
//  println(LeftFistYaw_value);
//  changeTransparent = map(changeTransparent, 10, 50, 0, 255);
//  stroke(0, 255-changeTransparent);
  
  // RIGHT HIP
  angleRhip = (RightRoll_value/float(127)) * PI;
  // RIGHT KNEE
  angleRknee = (RightIndexFlex_value/float(127)) * -PI;
  // RIGHT SHOULDER
  angleRshoulder = (RightMiddleFlex_value/float(127)) * PI;
  // RIGHT ELBOW
  angleRelbow = -(RightRingFlex_value/float(127)) * -PI;
  
  // LEFT HIP
  angleLhip = (LeftRoll_value/float(127)) * PI;
  // LEFT KNEE
  angleLknee = (LeftIndexFlex_value/float(127)) * -PI;
  // LEFT SHOULDER
  angleLshoulder = (LeftPitch_value/float(127)) * PI;
  // LEFT ELBOW
  angleLelbow = -(LeftRingFlex_value/float(127)) * -PI;
  
  
  // LEGS //
  strokeWeight(40);
  // RIGHT LEG:
  pushMatrix();
  segment(x, y, angleRhip, segLength);
  segment(segLength, 0, angleRknee, segLength);
  popMatrix();
  // LEFT LEG:
  pushMatrix();
  segment(x, y, angleLhip, segLength);
  segment(segLength, 0, angleLknee, segLength);
  popMatrix();
  
  // ARMS //
  strokeWeight(20);
  // RIGHT ARM:
  pushMatrix();
  translate(0, -100);
  segment(x, y, angleRshoulder, segLength/2);
  segment(segLength, 0, angleRelbow, segLength/2);
  popMatrix();
  //LEFT ARM:
  pushMatrix();
  translate(0, -100);
  segment(x, y, angleLshoulder, segLength/2);
  segment(segLength, 0, angleLelbow, segLength/2);
  popMatrix();
  
  strokeWeight(40);
  pushMatrix();
  line(x,y, x,y-100);
  ellipse(x,y-170,30,40);
  popMatrix();
}



void segment(float x, float y, float a, float segmentLength) {
  translate(x, y);
  rotate(a);
  line(0, 0, segmentLength, 0);
}



//void mousePressed() {
// // create an osc message
// OscMessage myMessage = new OscMessage("/test");
//
// myMessage.add(123); // add an int to the osc message
// myMessage.add(12.34); // add a float to the osc message
// myMessage.add("some text!"); // add a string to the osc message
//
// // send the message
// oscP5.send(myMessage, myRemoteLocation);
//}


