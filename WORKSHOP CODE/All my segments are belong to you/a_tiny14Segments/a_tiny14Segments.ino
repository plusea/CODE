/* 
 All my segments are blong to you" Workshop
 at Wear-It Festival 2014, Berlin/Germany
 >> http://www.kobakant.at/DIY/?p=5227
 
 Code for ATtiny that controls 14 individual
 segments of LED lights
 
 ATtiny45/85:
 RST -|  |- VCC
 Pin3 -|  |- Pin2
 Pin4 -|  |- Pin1
 GND -|  |- Pin0
 
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

int used14Segments[]={
  1,2,3,5,6,8,9,10,11,12,15,13,18,19};

int A_segments[]={
  7,3,18,12,9,6,1,5};
int B_segments[]={
  7,3,18,12,2,1,10,15};
int C_segments[]={
  4,15,3,18,12};
int D_segments[]={
  4,3,18,8,13};

int pause = 1;
int numberOfPins = 5;
int delayTime = 12;
int testDelay = 250;
int charliePin;

void setup(){
  for(int z=0;z<numberOfPins;z++) pinMode(led[z], OUTPUT);
  for(int z=0;z<numberOfPins;z++) digitalWrite(led[z], LOW);
}


void loop(){
  //testAll14LEDs();
  displayAlphabet(1, 100);
  displayAlphabet(2, 100);
  displayAlphabet(3, 100);
  displayAlphabet(4, 100);
  //displaySegment(13);
  //  translateAlphabet('A');
  //  delay(1000);
  //    translateAlphabet('B');
  //  delay(1000);

  //    for (int i=0;i<100;i++) {
  //  displayAlphabet(4);
  //    }
}



void testAll14LEDs(){
  for (int i=0;i<14;i++) {
    displaySegment(used14Segments[i]);
    delay(500);
  }
}






void translateAlphabet(char myABC){
  if(myABC == 'A') displayAlphabet(1, 1000);
  if(myABC == 'B') displayAlphabet(2, 1000);
  if(myABC == 'C') displayAlphabet(3, 1000);

}





void spwm(int freq,int spin,int sp){
  //on
  digitalWrite(spin,HIGH);
  delayMicroseconds(sp*freq);

  // off
  digitalWrite(spin,LOW);
  delayMicroseconds(sp*(255-freq));
} //spwm
























