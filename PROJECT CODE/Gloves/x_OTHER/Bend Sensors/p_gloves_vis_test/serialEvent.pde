void serialEvent (Serial myPort) {
  int h = 10;
  int [] constrainedValues = new int[8];
  int [] mappedValues = new int[8];

  /*
  int [] minValues = {
   500,70,450,80,400,100,500,250  };
   int [] maxValues = {
   600,240,900,250,500,400,600,350  };
   */
  int [] minValues = {
    0,0,0,0,0,0,0,0};
  int [] maxValues = {
    1023,1023,1023,1023,1023,1023,1023,1023};



  String inString = myPort.readStringUntil('\n');  // get the ASCII string:
  //fill(255);
  //rect(0,0,width,height);

  background(255);
  
  stroke(200,0,0);
  fill(0);

  if (inString != null) {  // if it's not empty:
    inString = trim(inString);    // trim off any whitespace:
    int incomingValues[] = int(split(inString, ","));  //split incoming values by comma

    if (incomingValues.length <= 9 && incomingValues.length > 0) {

      for(int i=0; i<8; i++){
        constrainedValues[i] = constrain(incomingValues[i], minValues[i],maxValues[i]);
        mappedValues[i] = int(map(constrainedValues[i], minValues[i],maxValues[i], 0, height));
        rect(i * width / 8, height - mappedValues[i], width / 8, h);
        println(mappedValues[4]);
      }

    }    
  }


}




