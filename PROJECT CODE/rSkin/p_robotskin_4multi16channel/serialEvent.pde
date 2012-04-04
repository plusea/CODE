void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');
  int x=0;
  int y=0;

  if (inString != null) {  // if it's not empty:
    inString = trim(inString);    // trim off any whitespace:
    int incomingValues[] = int(split(inString, ","));  //split incoming values by comma
    println(incomingValues.length);

    if (incomingValues.length <= cols+1 && incomingValues.length > 0) {
      
      // start loop at i=1 to skip row count
      for (int i = 1; i < incomingValues.length; i++) {
        //x = i-1;
        y = incomingValues[0];
        
        x = fleshRef[i-1];
        //y = skinRef[incomingValues[0]];
        
        rSkinArray[y][i] = incomingValues[i];
        
        float mappedValue = map(incomingValues[i], 0, 255, 0, 255);
        fill(mappedValue);
        stroke(200,0,0);
        rect(x*(width/cols), y*(height/rows), (width/cols),(height/rows));
        fill(255);
        //text(incomingValues[i], x*(width/cols), y*(height/rows));
        }
    }
  }
}

