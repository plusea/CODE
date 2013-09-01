import processing.serial.*;

import cc.arduino.*;

Arduino arduino;

color off = color(4, 79, 111);
color on = color(84, 145, 158);

void setup() {
  size(470, 280);
  println(Serial.list());
  arduino = new Arduino(this, Arduino.list()[4], 57600);
  

  arduino.pinMode(5, Arduino.INPUT);
  arduino.digitalWrite(5, Arduino.HIGH);

  //arduino.pinMode(16, Arduino.INPUT);
  arduino.digitalWrite(16, Arduino.HIGH);
}

void draw() {
  int digitalValue = arduino.digitalRead(5);
  int analogValue = arduino.analogRead(2);
  
  if (digitalValue == 1)
    fill(200, 0, 0);  
  else
    fill(0);
    rect(width/2, height/2, 100,100);
println(analogValue);
println(digitalValue);
//  ellipse(width/2, height/2, arduino.analogRead(2), arduino.analogRead(2));
}

