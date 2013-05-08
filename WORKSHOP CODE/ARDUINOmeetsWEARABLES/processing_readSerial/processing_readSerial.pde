import processing.serial.*;

int end = 10; // 10 is ASCII for lineend(return)
String serial;
Serial port; // opening a new serial port (creating a new serial object instance)

int x=0;
int y=0;



void setup() {
  // Serial.list();
  // initializing the serial object with port and baudrate. note that boudrate you set in Arduino should match with this speed
  port = new Serial(this, Serial.list()[0], 9600);
  port.clear();
  serial=port.readStringUntil(end);
  serial=null;
  size (400,400);
}

void draw (){
  background (153);
  fill (255);
  noStroke();
 while (port.available()>0){  
  serial = port.readStringUntil (end);
 }
 
 if (serial!= null){
  String[] a = split(serial, ',');
  println(a[0]);
  //println(a[1]);
  
  x=int(a[0]);
  y=int (a[1]);
  
  
 }
 
 ellipse(200,200,x/2,y/2);
}
