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
    0,0,0,0,0,0,0,0      };
  int [] maxValues = {
    1023,1023,1023,1023,1023,1023,1023,1023      };

  String inString = myPort.readStringUntil('\n');  // get the ASCII string:

  if (inString != null) {  // if it's not empty:
    inString = trim(inString);    // trim off any whitespace:
    int incomingValues[] = int(split(inString, ","));  //split incoming values by comma

    if (incomingValues.length <= 9 && incomingValues.length > 0) {

      for(int i=0; i<incomingValues.length; i++){

        strokeWeight(5);

        // GRAPH ALL

        /*
        // RAW DATA
         // map the incoming values (0 to  1023) to an appropriate
         // graphing range (0 to window height/number of values):        
         float ypos = map(incomingValues[i], 0, 1023, 0, height/incomingValues.length);
         
         // THRESHOLDED DATA
         //constrainedValues[i] = constrain(incomingValues[i], minValues[i],maxValues[i]);
         //float ypos = int(map(constrainedValues[i], minValues[i],maxValues[i], 0, height/incomingValues.length));
         
         // figure out the y position for this particular graph:
         float graphBottom = i * height/incomingValues.length;
         ypos = ypos + graphBottom;
         stroke(graphColor);
         line(xpos, height-previousValue[i], xpos+1, height-ypos);
         // save the current value to be the next time's previous value:
         previousValue[i] = ypos;
         */

        // map the incoming values (0 to  1023) to a graphing range for the followig calculation:
        //mappedValues[i] = map(incomingValues[i], 0,1023, 0,7);  
        //linearValues[i] = exp(mappedValues[i]-4);  //change from log to linear

        // GRAPH SELECT
        float ypos = map(incomingValues[i], 0, 1023, 0, height);
        float ylin = map(incomingValues[i], 0,1023, 0,7);  // map the incoming values (0 to  1023) to a graphing range for the following calculation
        ylin = exp(ylin-4) * 100;  //change from log to linear

        if(i==3) {
          stroke(200,0,0);
          strokeWeight(1);
          line(xpos, height-previousLin[i], xpos+1, height-ylin);
          strokeWeight(5);
          line(xpos, height-previousValue[i], xpos+1, height-ypos);
        }


        if(i==4) {
          stroke(0);
          strokeWeight(1);
          line(xpos, height-previousLin[i], xpos+1, height-ylin);
          strokeWeight(5);
          line(xpos, height-previousValue[i], xpos+1, height-ypos);
        }
        previousValue[i] = ypos;
        previousLin[i] = ylin;
      }



    }

    if(millis() - time > 5000){
      text(millis()/1000, xpos, height);
      time = millis();
    }

    // if you've drawn to the edge of the window, start at the beginning again:
    if (xpos >= width) {
      saveFrame();
      xpos = 0;
      colorCount++;
      if(colorCount == 1) graphColor = color(200,0,0);
      if(colorCount == 2) graphColor = color(0,200,0);
      if(colorCount == 3) graphColor = color(0,0,200);
      if(colorCount == 4) colorCount = 0;
      //background(255);
      //grid();
    } 
    else {
      xpos+=2;
    }
  }        
}







