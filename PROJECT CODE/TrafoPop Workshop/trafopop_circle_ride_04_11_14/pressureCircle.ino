inline void pressureCircle() {

  pressureValue = analogRead(A3);  // read sensor value
  Serial.print(pressureValue);  // print sensor value to serial port for debugging
  Serial.print("\t");  // print sensor value to serial port for debugging
  pressureValue = constrain(pressureValue, 0, 1023);  // map sensor value to number of LEDs
  pressureValue = map(pressureValue, 0, 1023, 0, 255);  // map sensor value to number of LEDs
  Serial.println(pressureValue);  // print sensor value to serial port for debugging


  red = pressureValue;
  blue = 255-pressureValue;
  green = 0;    


  struct color myColor = { 
    red, green, blue
  };

  for(int i=3; i<=20; i++) {
    pixels[i] = myColor;
  }


  show((byte *)pixels, sizeof(pixels));  // update pixels
}








