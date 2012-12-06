void grid(){

  for(int i=1; i<height; i+=height/(10*numberOfCorners)){
    strokeWeight(0.5);
    line(0 , i , width , i);
  }
  
  for(int i=1; i<height; i+=height/(numberOfCorners)){
    strokeWeight(2);
    line(0 , i , width , i);
  }

}


