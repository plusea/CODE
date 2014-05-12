inline void draw4()
{
  count++;
  if(count % 50 == 0) {
    pixels[0] = colorOFF;
    pixels[1] = colorON;
  }
  if(count % 100 == 0) {
    pixels[0] = colorON;
    pixels[1] = colorOFF;
  }
  if(count > 100) count = 0;
  
  
  
  for (byte i = 2; i <= NUM; i++){    

    if(i < sensorValue) {
      red = 1;
      blue = 1;
      green = 1;
    }
    else {
      red = 0;
      blue = 0;
      green = 0;    
    }
    
    struct color color2 =
    { 
      max(0,red * 255), max(0,green * 255), max(0,blue * 255)
    };
    
      pixels[i] = color2;
  }


//  if(fadeCount < 200) fadeAmount = +1;
//  if(fadeCount > 255) {
//    fadeAmount = -1;
//    delay(1000);
//  }
//  delay(5);
//
//  fadeCount = sensorValue;  //+=fadeAmount;

}



