void serialEvent (Serial myPort) {

  String inString = myPort.readStringUntil('\n');  // get the ASCII string

  if (inString != null) {  // if it's not empty
  
    inString = trim(inString);  // trim off any whitespace
    int incomingValues[] = int(split(inString, ","));  // convert to an array of ints
    print(incomingValues.length);
    print("\t");
    println(incomingValues[0]);

    if (incomingValues.length <= maxNumberOfSensors && incomingValues.length > 0) {

      for (int i = 0; i < incomingValues.length; i++) {
        float mappedValue = map(incomingValues[i], 0, 950, 0, 255);
          fill(255-mappedValue);
          stroke(200,0,0);
          rect(x*(width/cols), y*(height/rows), (width/cols),(height/rows));
          if (fontInitialized) {
          fill(0);
          text(incomingValues[i], x*(width/rows) + rows, y*(height/cols) + cols*3);
        }
          x++;
          if(x == cols){
            x=0;
            y++;
          }
          if(y == rows){
            y=0;
          }
          
        } //end for
      } //end if
    } // end if
}// end void serial event

