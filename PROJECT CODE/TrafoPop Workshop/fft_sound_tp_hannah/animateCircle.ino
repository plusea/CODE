void animateCircle(){

  for(int r=5; r>0; r--){ 

    if(r % 1 == 0) { 
      myColor = colorON; 
      circleSpeed = 10; 
    }
    if(r % 2 == 0) {  
      myColor = colorRed; 
      circleSpeed = 20; 
    }
    if(r % 3 == 0) { 
      myColor = colorPurple; 
      circleSpeed = 30; 
    }
    if(r % 4 == 0) { 
      myColor = colorTurquoise; 
      circleSpeed = 40; 
    }
    if(r % 5 == 0) { 
      myColor = colorYellow; 
      circleSpeed = 50; 
    }


      for(int h=3; h<=20; h++){ 

        for(int i=3; i<=20; i++) allOFF();

        //    struct color randomColor = { 
        //    random(1,255), random(1,255), random(1,255)
        //    };
        pixels[0] = myColor;
        pixels[1] = myColor;
        pixels[h-1] = myColor;
        pixels[h] = myColor;
        pixels[h+1] = myColor;

        show2((byte *)pixels, sizeof(pixels));  // update pixels
        delay(circleSpeed);

      }
    }



}












