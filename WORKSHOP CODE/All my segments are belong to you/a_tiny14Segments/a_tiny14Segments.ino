/* 
 All my segments are blong to you" Workshop
 at Wear-It Festival 2014, Berlin/Germany
 >> http://www.kobakant.at/DIY/?p=5227
 
 Code for ATtiny that controls 14 individual
 segments of LED lights
 
 
   ATtiny45/85:
       ____
  RST -|  |- VCC
 Pin3 -|  |- Pin2
 Pin4 -|  |- Pin1
  GND -|  |- Pin0
       ____
 
 
 displaySegmenting Segments:
 +/-  0    1    2     3    4
 0   X   s1   s2    s3   s4
 2   s5   X   s6    s7   s8
 3   s9  s10   X    s11  s12
 4   s13 s14  s15    X   s16
 5   s17 s18  s19   s20   X
 */


// define ATtiny pins that will be used for displaySegmenting:
int led[]={
  0,1,2,3,4};

// for testing purposes, list all segments used in design:
int used14Segments[]={
  1,2,3,5,6,8,9,10,11,12,15,13,18,19};

// define which segments are used in which letters of the ABC:
int A_segments[]={
  7,3,18,12,9,6,1,5};
int B_segments[]={
  7,3,18,12,2,1,10,15};
int C_segments[]={
  4,15,3,18,12};
int D_segments[]={
  4,3,18,8,13};
int E_segments[]={
  6,15,3,18,12,1,5};
int F_segments[]={
  5,3,18,12,1,5};
int G_segments[]={
  6,5,6,15,3,18,12};
int H_segments[]={
  6,3,18,1,5,9,6};
int I_segments[]={
  4,12,19,11,15};
int J_segments[]={
  4,3,9,6,15};
int K_segments[]={
  6,3,18,1,2,10};
int L_segments[]={
  3,15,3,18};
int M_segments[]={
  6,3,18,8,2,9,6};
int N_segments[]={
  6,3,18,8,10,6,9};
int O_segments[]={
  6,3,18,12,9,6,15};
int P_segments[]={
  6,3,18,12,9,5,1};
int Q_segments[]={
  7,3,18,12,9,6,15,10};
int R_segments[]={
  7,3,18,12,9,5,1,10};
int S_segments[]={
  6,12,18,1,5,6,15};
int T_segments[]={
  3,12,19,11};
int U_segments[]={
  5,18,3,15,6,9};
int V_segments[]={
  4,18,3,13,2};
int W_segments[]={
  6,18,3,13,10,6,9};
int X_segments[]={
  4,8,10,2,13};
int Y_segments[]={
<<<<<<< HEAD
3,8,2,11};
int Z_segments[]={
4,12,2,13,15};


int pause = 1;
=======
  3,8,2,11};
int Z_segments[]={
  4,12,2,13,15};

int pause = 1;  // pause very very briefly after displaying each segment
>>>>>>> d66945ce18a21ba51ebd72d226cb912246dfe248
int numberOfPins = 5;



void setup(){
  for(int z=0;z<numberOfPins;z++) pinMode(led[z], OUTPUT);
  for(int z=0;z<numberOfPins;z++) digitalWrite(led[z], LOW);
}



void loop(){
  // TESTS:
  //testAll20LEDs();
  //testAll14LEDs();
<<<<<<< HEAD
=======
  // displaySegment(13);
>>>>>>> d66945ce18a21ba51ebd72d226cb912246dfe248

  // Display A, B, C....:
  for (int i=1;i<=26;i++) {
    displayAlphabet(i, 200);
  }
<<<<<<< HEAD

  // displaySegment(13);

  //  translateAlphabet('A');
  //  delay(1000);
  //    translateAlphabet('B');
  //  delay(1000);

  //    for (int i=0;i<100;i++) {
  //  displayAlphabet(4);
  //    }
=======
>>>>>>> d66945ce18a21ba51ebd72d226cb912246dfe248
}



void testAll14LEDs(){
  for (int i=0;i<14;i++) {
    displaySegment(used14Segments[i]);
    delay(100);
  }
}


void testAll20LEDs(){
  for (int i=1;i<=20;i++) {
    displaySegment(i);
    delay(3000);
  }
}


<<<<<<< HEAD




void translateAlphabet(char myABC){
  if(myABC == 'A') displayAlphabet(1, 1000);
  if(myABC == 'B') displayAlphabet(2, 1000);
  if(myABC == 'C') displayAlphabet(3, 1000);
  if(myABC == 'D') displayAlphabet(4, 1000);
  if(myABC == 'E') displayAlphabet(5, 1000);

}





void spwm(int freq,int spin,int sp){
  //on
  digitalWrite(spin,HIGH);
  delayMicroseconds(sp*freq);

  // off
  digitalWrite(spin,LOW);
  delayMicroseconds(sp*(255-freq));
} //spwm



























=======
void testAll20LEDs(){
  for (int i=1;i<=20;i++) {
    displaySegment(i);
    delay(500);
  }
}
>>>>>>> d66945ce18a21ba51ebd72d226cb912246dfe248
