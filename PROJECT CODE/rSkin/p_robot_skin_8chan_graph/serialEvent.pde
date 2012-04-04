void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');
  int x=0;
  int y=0;

  if (inString != null) {  // if it's not empty:
    inString = trim(inString);    // trim off any whitespace:
    int incomingValues[] = int(split(inString, ","));  //split incoming values by comma
    println(incomingValues[0]);
    println(incomingValues[10]);


    if (incomingValues.length <= maxNumberOfSensors && incomingValues.length > 0) {
      
      for (int i = 0; i < incomingValues.length; i++) {

        float mappedValue = map(incomingValues[i], 0, 1023, 0, 255);
        fill(mappedValue);
        rect(x*100, y*100, 100,100);
        x++;
        if(x == 8){
          x=0;
          y++;
        }
        if(y == 8){
        y=0;
        }


    }
  }
}
}
