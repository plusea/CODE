/*Software PWM on Attiny85
 Ernst Christensen 16.okt. 2011
 copied from here: http://arduino.cc/forum/index.php/topic,75334.0.html
 */

int led[]={
  2,1,0,4,3};
int count=0;
int delayTime = 18;

void setup(){
  for (int z=0;z<5;z++){
    pinMode(led[z],OUTPUT);
  } //for z

}


void loop(){
  

  for(int i = 0; i<5; i++){
    for (int x=1;x<254;x++){
      spwm(x,led[count],delayTime);
    }
    for (int x=254;x>1;x--){
      spwm(x,led[count],delayTime);
    }
    count++;
    if (count>4){
      count=0;
    }
  }




  for(int i = 0; i<1; i++){
    for (int x=1;x<254;x++){
      spwm(x,led[0],delayTime);
      spwm(x,led[1],delayTime);
    }
    for (int x=254;x>1;x--){
      spwm(x,led[0],delayTime);
      spwm(x,led[1],delayTime);
    }
  }
  for(int i = 0; i<1; i++){
    for (int x=1;x<254;x++){
      spwm(x,led[1],delayTime);
      spwm(x,led[2],delayTime);
    }
    for (int x=254;x>1;x--){
      spwm(x,led[1],delayTime);
      spwm(x,led[2],delayTime);
    }
  }
  for(int i = 0; i<1; i++){
    for (int x=1;x<254;x++){
      spwm(x,led[2],delayTime);
      spwm(x,led[3],delayTime);
    }
    for (int x=254;x>1;x--){
      spwm(x,led[2],delayTime);
      spwm(x,led[3],delayTime);
    }
  }
  for(int i = 0; i<1; i++){
    for (int x=1;x<254;x++){
      spwm(x,led[3],delayTime);
      spwm(x,led[4],delayTime);
    }
    for (int x=254;x>1;x--){
      spwm(x,led[3],delayTime);
      spwm(x,led[4],delayTime);
    }
  }






  for(int i = 0; i<1; i++){
    for (int x=1;x<254;x++){
      spwm(x,led[0],delayTime);
      spwm(x,led[1],delayTime);
      spwm(x,led[2],delayTime);
    }
    for (int x=254;x>1;x--){
      spwm(x,led[0],delayTime);
      spwm(x,led[1],delayTime);
      spwm(x,led[2],delayTime);
    }
  }
  for(int i = 0; i<1; i++){
    for (int x=1;x<254;x++){
      spwm(x,led[1],delayTime);
      spwm(x,led[2],delayTime);
      spwm(x,led[3],delayTime);
    }
    for (int x=254;x>1;x--){
      spwm(x,led[1],delayTime);
      spwm(x,led[2],delayTime);
      spwm(x,led[3],delayTime);
    }
  }
  for(int i = 0; i<1; i++){
    for (int x=1;x<254;x++){
      spwm(x,led[2],delayTime);
      spwm(x,led[3],delayTime);
      spwm(x,led[4],delayTime);
    }
    for (int x=254;x>1;x--){
      spwm(x,led[2],delayTime);
      spwm(x,led[3],delayTime);
      spwm(x,led[4],delayTime);
    }
  }




  for(int i = 0; i<1; i++){
    for (int x=1;x<254;x++){
      spwm(x,led[0],delayTime);
      spwm(x,led[1],delayTime);
      spwm(x,led[2],delayTime);
      spwm(x,led[3],delayTime);
    }
    for (int x=254;x>1;x--){
      spwm(x,led[0],delayTime);
      spwm(x,led[1],delayTime);
      spwm(x,led[2],delayTime);
      spwm(x,led[3],delayTime);
    }
  }  
  for(int i = 0; i<1; i++){
    for (int x=1;x<254;x++){
      spwm(x,led[1],delayTime);
      spwm(x,led[2],delayTime);
      spwm(x,led[3],delayTime);
      spwm(x,led[4],delayTime);
    }
    for (int x=254;x>1;x--){
      spwm(x,led[1],delayTime);
      spwm(x,led[2],delayTime);
      spwm(x,led[3],delayTime);
      spwm(x,led[4],delayTime);
    }
  }








  for(int i = 0; i<1; i++){
    for (int x=1;x<254;x++){
      spwm(x,led[0],delayTime);
      spwm(x,led[1],delayTime);
      spwm(x,led[2],delayTime);
      spwm(x,led[3],delayTime);
      spwm(x,led[4],delayTime);
    }
    for (int x=254;x>1;x--){
      spwm(x,led[0],delayTime);
      spwm(x,led[1],delayTime);
      spwm(x,led[2],delayTime);
      spwm(x,led[3],delayTime);
      spwm(x,led[4],delayTime);
    }
  }



}


void spwm(int freq,int pin,int sp){

  //on
  digitalWrite(pin,HIGH);
  delayMicroseconds(sp*freq);

  // off
  digitalWrite(pin,LOW);
  delayMicroseconds(sp*(255-freq));


} //spwm







