void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');
  int x=0;
  int y=0;

  if (inString != null) {  // if it's not empty:
    inString = trim(inString);    // trim off any whitespace:
    int incomingValues[] = int(split(inString, ","));  //split incoming values by comma
println(incomingValues.length);

    if (incomingValues.length <= maxNumberOfSensors && incomingValues.length > 0) {
      
      for (int i = 0; i < incomingValues.length; i++) {

        float mappedValue = map(incomingValues[i], 0, 1023, 0, 255);
        fill(mappedValue);
        stroke(200,0,0);
        rect(x*(width/28), y*(height/28), (width/28),(height/28));
        x++;
        if(x == 28){
          x=0;
          y++;
        }
        if(y == 28){
        y=0;
        }


    }
  }
}
}
