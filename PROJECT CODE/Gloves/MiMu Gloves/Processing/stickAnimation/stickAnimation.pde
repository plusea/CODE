import oscP5.*;
import netP5.*;
OscP5 oscP5;
NetAddress myRemoteLocation;
// global puppeteer variables:
int roll;
float LeftFistRoll_value;
float LeftIndexFlex_value;
float LeftFistYaw_value;
float x, y;
float angle1 = 0.0;
float angle2 = 0.0;
float segLength = 200;
void setup() {
// start oscP5, telling it to listen for incoming messages at port 5001 */
oscP5 = new OscP5(this, 9000);
// set the remote location to be the localhost on port 5001
myRemoteLocation = new NetAddress("127.0.0.1", 9000);
//size(640, 360);
size(displayWidth, displayHeight);
strokeWeight(60);
stroke(0, 160);
x = width * 0.6;
y = height * 0.5;
}
void draw()
{
background(255);
angle2 = (LeftIndexFlex_value/float(127) - 0.5) * -PI;
angle1 = (LeftFistRoll_value/float(127) - 0.5) * PI;
float changeTransparent = LeftFistYaw_value;
println(LeftFistYaw_value);
changeTransparent = map(changeTransparent, 10, 50, 0, 255);
stroke(0, 255-changeTransparent);
pushMatrix();
segment(x, y, angle1);
segment(segLength, 0, angle2);
popMatrix();
}
void segment(float x, float y, float a) {
translate(x, y);
rotate(a);
line(0, 0, segLength, 0);
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
void oscEvent(OscMessage theOscMessage)
{
String addrPattern = theOscMessage.addrPattern();
// Print address pattern to terminal
//println(addrPattern);
// LEFT FIST ROLL
if (addrPattern.equals("/LeftFistRoll")) {
LeftFistRoll_value = theOscMessage.get(0).floatValue();
}
// LEFT INDEX FLEX
if (addrPattern.equals("/LeftIndexFlex")) {
LeftIndexFlex_value = theOscMessage.get(0).floatValue();
}
// LEFT FIST YAW
if (addrPattern.equals("/LeftFistYaw")) {
LeftFistYaw_value = theOscMessage.get(0).floatValue();
}
println(LeftFistRoll_value);
println(LeftIndexFlex_value);
println(LeftFistYaw_value);
// get the first value as an integer
//float firstValue = theOscMessage.get(0).floatValue();
//float secondValue = theOscMessage.get(1).floatValue();
//roll = int(firstValue);
// // get the second value as a float
// float secondValue = theOscMessage.get(1).floatValue();
//
// // get the third value as a string
// String thirdValue = theOscMessage.get(2).stringValue();
//
// // print out the message
// print("OSC Message Recieved: ");
// print(theOscMessage.addrPattern() + " ");
//println(firstValue);
//println(secondValue);
}
