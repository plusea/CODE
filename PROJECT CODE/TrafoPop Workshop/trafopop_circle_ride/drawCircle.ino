inline void drawCircle() {

  sensorValue = analogRead(A1);  // read sensor value
  Serial.print(sensorValue);  // print sensor value to serial port for debugging
  Serial.print("\t");  // print sensor value to serial port for debugging
  sensorValue = constrain(sensorValue, 50, 1000);  // map sensor value to number of LEDs
  sensorValue = map(sensorValue, 50, 1000, 0, LEDtotal+1);  // map sensor value to number of LEDs
  Serial.println(sensorValue);  // print sensor value to serial port for debugging

  // only if sensor is touched should it update LEDs on/off, otherwise keep last state:
  if(sensorValue != LEDtotal+1) {

    count++;  // keep track of cycles

    if(count % 50 == 0) {
      pixels[0] = colorOFF;
      pixels[1] = colorON;
    }

    if(count % 100 == 0) {
      pixels[0] = colorON;
      pixels[1] = colorOFF;
    }

    if(count > 100) count = 0;  // reset count

    for (int i=2; i<=LEDtotal; i++){    
      if(i < sensorValue) {  // turn all LEDs less than position on wheel ON
        red = 255;
        blue = 255;
        green = 255;
      }
      else {    // turn all LEDs greater than position on wheel OFF
        red = 0;
        blue = 0;
        green = 0;    
      }

      struct color myColor = { 
        red, green, blue
      };

      pixels[i] = myColor;
    }

    fadeCount = sensorValue;  //+=fadeAmount;

  }
  
  show((byte *)pixels, sizeof(pixels));  // update pixels
}







