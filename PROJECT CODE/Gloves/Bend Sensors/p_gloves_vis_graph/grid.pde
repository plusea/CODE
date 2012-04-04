void grid(){
  
String [] fingers = {"Thumb", "Index_a", "Index_b", "Middle_a", "Middle_b", "Ring_a", "Ring_b", "Little"};

  for(int i=1; i<height; i+=height/(10*maxNumberOfSensors)){
    strokeWeight(0.25);
    line(0 , i , width , i);
  }
  
  /*
  for(int i=1; i<height; i+=height/maxNumberOfSensors){
    strokeWeight(1);
    fill(0);
    text(fingers[7 - i / (height/maxNumberOfSensors)], 10, i+14);
    line(0 , i , width , i);
  }
  */

}


