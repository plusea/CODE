// super basic 
// over-all volume controlls how many LEDs light up


void graph(){  

  for(int i=0;i<NUM;i++) {
    // if frequencies in range data[9,10,11] are loud:
    if(i<input) {
      pixels[i] = colorPurple;
    }
    else { 
      pixels[i] = colorOFF;
    }
  }
  
}




