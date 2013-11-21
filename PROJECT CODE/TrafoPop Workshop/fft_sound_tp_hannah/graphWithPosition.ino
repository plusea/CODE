// super basic 
// over-all volume controlls how many LEDs light up


void graphwithPosition(){  
  int threshold = 1;
  int averageVolume = 0;
  
  // go through all the LEDs:
  for(int meh=0;meh<128;meh++) {

    Serial.println(int(data[meh]));

    if(data[meh] > threshold) {
      averageVolume++;
    }
  }

  averageVolume = map(averageVolume, 0, 128, 0, NUM);

  for(int i=0;i<NUM;i++) {
    // if frequencies in range data[9,10,11] are loud:
    if(i<averageVolume) {
      pixels[i] = colorRed;
    }
    else { 
      pixels[i] = colorOFF;
    }
  }
  
}




