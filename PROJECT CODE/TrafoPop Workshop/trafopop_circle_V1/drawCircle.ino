inline void drawCircle() {

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

  for (byte i = 2; i <= NUM; i++){    
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





