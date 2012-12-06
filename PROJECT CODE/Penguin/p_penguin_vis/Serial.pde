////////////////////////////////////
////////////    SERIAL   ///////////
////////////////////////////////////
void serialEvent(Serial thisPort) {

  String incomingString = penguinPort.readStringUntil('\n');  // get the ASCII string
  if (incomingString != null) {  // if it's not empty
    incomingString = trim(incomingString);  // trim off any whitespace
    int penguinTalk[] = int(split(incomingString, ","));  // convert to an array of ints
    rightWing = penguinTalk[1];
    leftWing = penguinTalk[0];
    squeezeAmount = penguinTalk[2];
    tiltDirection = penguinTalk[3];
    Ax = penguinTalk[4];
    Ay = penguinTalk[5];
    Az = penguinTalk[6];
  }
}





