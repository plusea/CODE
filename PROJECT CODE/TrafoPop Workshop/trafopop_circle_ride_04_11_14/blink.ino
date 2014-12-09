void blinkAll(){
  allOFF();
  show((byte *)pixels, sizeof(pixels));  // update pixels
  delay(100);
  allON();
  show((byte *)pixels, sizeof(pixels));  // update pixels
  delay(100);
  
}
