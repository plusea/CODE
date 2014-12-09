inline void pressureCircle() {

  pressureValue = analogRead(A3);  // read sensor value
  Serial.print(pressureValue);  // print sensor value to serial port for debugging
  Serial.print("\t");  // print sensor value to serial port for debugging
  pressureValue = constrain(pressureValue, 40, 700);  // map sensor value to number of LEDs
  pressureValue = map(pressureValue, 40, 700, 0, 255);  // map sensor value to number of LEDs
  Serial.print(pressureValue);  // print sensor value to serial port for debugging
  Serial.print("\t");  // print sensor value to serial port for debugging
  int pressureLEDs = map(pressureValue, 0, 255, 20, 2);
  Serial.println(pressureLEDs);

  red = 255-pressureValue;
  blue = pressureValue;
  green = 0;    


  struct color myColor = { 
    red, green, blue
  };


  for(int i=0; i<=20; i++) {
    allOFF();
  }

  for(int i=0; i<=pressureLEDs; i++) {
    pixels[0] = myColor;
    pixels[1] = myColor;
    pixels[i+2] = myColor;
  }

  show((byte *)pixels, sizeof(pixels));  // update pixels
  delay(circleSpeed);
}










