int transferValues[] = new int[numberOfCorners];
float mappedValues[] = new float[numberOfCorners];
float linearValues[] = new float[numberOfCorners];
float psValue = 0;


void serialEvent (Serial myPort) {
  String inString = myPort.readStringUntil('\n');  // get the ASCII string:

  if (inString != null) {  // if it's not empty:    
    inString = trim(inString);  // trim off any whitespace:
    int incomingValues[] = int(split(inString, ","));  // convert to an array of ints:
    psValue = map(incomingValues[4], 0,1023, 0,400);
    println("pressure sensor value: " + psValue);
    for(int i=0; i<numberOfCorners; i++)
      transferValues[i] = incomingValues[i];
    //println("transfer values: " + transferValues[0]);
  }

  mapping();
  //graph();
  square();
}


void mapping(){
  for (int i = 0; i < numberOfCorners; i++) {

    mappedValues[i] = map(transferValues[i], 0,1023, 0,7);  // map the incoming values (0 to  1023) to a graphing range for the following calculation
    linearValues[i] = exp(mappedValues[i]-4);  //change from log to linear
    //println("mapped values: " + mappedValues[0]);
    //println("linear values: " + linearValues[0]);
  }
}


void graph(){

  for (int i = 0; i < numberOfCorners; i++) {

    float ypos = map(linearValues[i], 0, 20, 0, height/numberOfCorners);
    float ycompare = map(transferValues[i], 0, 1023, 0, height/numberOfCorners);

    float graphBottom = i * height/numberOfCorners;  // figure out the y position for this particular graph:

    ypos = ypos + graphBottom;
    ycompare = ycompare + graphBottom;

    //if(i==0) println("ypos: " + ypos);

    stroke(0);
    strokeWeight(2);
    line(xpos, height-previousValue[i], xpos+1, height-ypos);
    previousValue[i] = ypos;  // save the current value to be the next time's previous value:

    stroke(200,0,0);
    line(xpos, height-previousTransferValue[i], xpos+1, height-ycompare);
    previousTransferValue[i] = ycompare;
  }


  // if you've drawn to the edge of the window, start at the beginning again:
  if (xpos >= width) {
    saveFrame();
    xpos = 0;
    background(255);
  } 
  else xpos+=1;

}





void square(){
  background(255);
  noFill();
  float sv = 600  ;  //velostat 65, eeontex 38 600
  int ssv = 200;


  strokeWeight(5);
  stroke(0);
  
rectMode(CENTER);
  //fill(200,0,0,255-psValue);
  rect(width/2, height/2, 2*ssv, 2*ssv);
  
    rectMode(CORNER);
    fill(200,0,0);
    stroke(200,0,0);
  rect(width/2-(ssv+60), height/2+ssv, 50, -psValue);



  float corner0 = linearValues[0] * sv;
  float corner1 = linearValues[1] * sv;
  float corner2 = linearValues[2] * sv;
  float corner3 = linearValues[3] * sv;

  println("corner0=" + corner0);
  noStroke();
  fill(0,0,0,50);
  ellipse(width/2-ssv, height/2-ssv, corner0, corner0);
  ellipse(width/2-ssv, height/2+ssv, corner1, corner1);
  ellipse(width/2+ssv, height/2+ssv, corner2, corner2);
  ellipse(width/2+ssv, height/2-ssv, corner3, corner3);


}




/*

 
 
 // make a black block to erase the previous text:
 noStroke();
 fill(255);
 rect(10, graphBottom+1, 110, 20);
 
 // print the sensor numbers to the screen:
 fill(0);
 int textPos = int(graphBottom) + 14;
 // sometimes serialEvent() can happen before setup() is done.
 // so you need to make sure the font is initialized before
 // you text():
 if (fontInitialized) text("Sensor " + i + ":" + transferValues[i], 10, textPos);
 
 */



