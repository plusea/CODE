void displayAlphabet(int myNumber, int myTime){
  switch(myNumber){

    // A
  case 1:
    for (int i=0;i<myTime;i++) {
      for (int j=1;j<A_segments[0]+1;j++) {
        displaySegment(A_segments[j]);
      }
    }
    break;

    // B
  case 2:
    for (int i=0;i<myTime;i++) {
      for (int j=1;j<B_segments[0]+1;j++) {
        displaySegment(B_segments[j]);
      }
    }
    break;

    // C
  case 3:
    for (int i=0;i<myTime;i++) {
      for (int j=1;j<C_segments[0]+1;j++) {
        displaySegment(C_segments[j]);
      }
    }
    break;


    // D
  case 4:
    for (int i=0;i<myTime;i++) {
      for (int j=1;j<D_segments[0]+1;j++) {
        displaySegment(D_segments[j]);
      }
    }
    break;
  }
}
