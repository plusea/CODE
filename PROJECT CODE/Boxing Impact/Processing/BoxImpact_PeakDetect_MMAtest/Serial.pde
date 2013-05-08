////////////////////////////////////
////////////    SERIAL   ///////////
////////////////////////////////////
void serialEvent(Serial thisPort) {
    String rightString = rightPort.readStringUntil('\n');  // get the ASCII string
    if (rightString != null) {  // if it's not empty
      rightString = trim(rightString);  // trim off any whitespace
      int rightValues[] = int(split(rightString, ","));  // convert to an array of ints
      rightPS = 1023 - rightValues[0];
      leftPS = 1023 - rightValues[1];
      //println("RIGHT: PS: " + rightPS + " PSmap: " + rightPSmap + " X: " + rightX + " Y: " + rightY + " Z: " + rightZ);
    }

}

