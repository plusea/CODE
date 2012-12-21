void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');

  // if it's not empty:
  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);

    // convert to an array of ints:
    int incomingValues[] = int(split(inString, ","));

    // print out the values
    //  print("length: " + incomingValues.length + " values.\t");
    if (incomingValues.length <= maxNumberOfSensors && incomingValues.length > 0) {
      for (int i = 0; i < incomingValues.length; i++) {

        // map the incoming values (0 to  1023) to an appropriate
        // graphing range (0 to window height/number of values):
        float ypos = map(incomingValues[i], 0, 1023, 0, height/incomingValues.length);

        // figure out the y position for this particular graph:
        float graphBottom = i * height/incomingValues.length;
        ypos = ypos + graphBottom;

        // make a black block to erase the previous text:
        noStroke();
        fill(255);
        //rect(10, graphBottom+1, 110, 20);

        // print the sensor numbers to the screen:
        fill(0);
        int textPos = int(graphBottom) + 14;
        // sometimes serialEvent() can happen before setup() is done.
        // so you need to make sure the font is initialized before
        // you text():
        if (fontInitialized) {
          //text("Sensor " + i + ":" + incomingValues[i], 10, textPos);
        }

        stroke(0);
        strokeWeight(5);
        line(xpos, height-previousValue[i], xpos+1, height-ypos);
        // save the current value to be the next time's previous value:
        previousValue[i] = ypos;
      }
    }
    // if you've drawn to the edge of the window, start at the beginning again:
    if (xpos >= width) {
      saveFrame();
      xpos = 0;
      background(255);
    } 
    else {
      xpos+=1;
    }
  }
}
