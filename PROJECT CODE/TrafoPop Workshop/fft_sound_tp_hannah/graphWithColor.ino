// use the LEDs like a graph
// frequencies represented by position of LED
// volume represented by colour of LED

void graphWithColor(){  

  // go through all the LEDs:
  for( int meh=0;meh<NUM;meh++)
  {

    // if frequencies in range data[9,10,11] are loud:
    if( (data[meh*3]>6) || (data[meh*3+1]>6)|| (data[meh*3+2]>6)) {
      pixels[meh] = colorRed;
      //        color2.r=255;  
      //        color2.g=0;
      //        color2.b=0;
    }

    // if frequencies in range data[6,7,8] are loud:
    else if( (data[meh*3]>4) || (data[meh*3+1]>4)|| (data[meh*3+2]>4)) {
      pixels[meh] = colorON;

    }

    // if frequencies in range data[3,4,5] are loud:
    else if( (data[meh*3]>2) || (data[meh*3+1]>2)|| (data[meh*3+2]>2)) {
      pixels[meh] = colorYellow;
    }

    // if frequencies in range data[0,1,2] are loud:
    else if( (data[meh*3]>1) || (data[meh*3+1]>1)|| (data[meh*3+2]>1)) {
      pixels[meh] = colorOFF;
    }

    // if frequencies in range 1 are loud:
    else {
      pixels[meh] = colorOFF;
    }
  }
}



