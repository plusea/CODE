// use the LEDs like a graph
// frequencies represented by position of LED
// volume represented by colour of LED

void graphSoundWithColors(){  

  // go through all the LEDs:
  for( int meh=0;meh<NUM;meh++)
  {

int freq = 3;
if( (data[meh*freq]>6) || (data[meh*freq+1]>6) || (data[meh*freq+2]>6)) pixels[meh] = colorRed;
else if( (data[meh*freq]>4) || (data[meh*freq+1]>4) || (data[meh*freq+2]>4)) pixels[meh] = colorOrange;
else if( (data[meh*freq]>2) || (data[meh*freq+1]>2) || (data[meh*freq+2]>2)) pixels[meh] = colorYellow;
else pixels[meh] = colorOFF;

//    int freq = 3;
//    if( (data[meh*freq]>8) || (data[meh*freq+1]>8) || (data[meh*freq+2]>8)) pixels[meh] = colorRed;
//    else if( (data[meh*freq]>6) || (data[meh*freq+1]>6) || (data[meh*freq+2]>6)) pixels[meh] = colorBlue;
//    else if( (data[meh*freq]>4) || (data[meh*freq+1]>4) || (data[meh*freq+2]>4)) pixels[meh] = colorOrange;
//    else if( (data[meh*freq]>2) || (data[meh*freq+1]>2) || (data[meh*freq+2]>2)) pixels[meh] = colorTurquoise;
//    else if( (data[meh*freq]>1) || (data[meh*freq+1]>1) || (data[meh*freq+2]>1)) pixels[meh] = colorOFF;
//    else pixels[meh] = colorOFF;
    //    


  }
}




