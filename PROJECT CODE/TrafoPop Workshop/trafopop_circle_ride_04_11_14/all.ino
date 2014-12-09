void allON(){
  
  for (int i = 0; i <= 20; i++){ 
    pixels[i] = colorON;
  }

//show((byte *)pixels, sizeof(pixels));  // update pixels

}

void allOFF(){
  
  for (int i = 0; i <= 20; i++){ 
    pixels[i] = colorOFF;
  }

//show((byte *)pixels, sizeof(pixels));  // update pixels

}
