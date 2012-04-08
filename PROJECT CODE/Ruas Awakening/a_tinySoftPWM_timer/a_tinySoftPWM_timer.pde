/*Software PWM on Attiny85
Ernst Christensen 16.okt. 2011
*/

// teensy:
/*
int ledGND[]={3,4,5,6,7,8,9};
int ledPOS[]={11,12,13,14,15,16,17,22};
int ledGNDsize = sizeof(ledGND);
int ledPOSsize = sizeof(ledPOS);
*/

int led[]={0,1,2};
int ledSize = sizeof(led);
int count=0;




void setup(){
for (int z=0;z<ledSize;z++) pinMode(led[z],OUTPUT);
}





void loop(){

for (int x=1;x<254;x++){
  spwmSIN(x,led[count],5);
}
for (int x=254;x>1;x--){
  spwmSIN(x,led[count],5);
}

count++;
  if (count > 2){
count=0;
}

}


void spwmSIN(int freq,int spin,int sp){
  //on
  
//float brightness = (1 + sin(freq * count * PI + freq)) * 0.5:
  
digitalWrite(spin,HIGH);
delayMicroseconds(sp*freq);

// off
digitalWrite(spin,LOW);
delayMicroseconds(sp*(255-freq));
} //spwm



/*
void spwm(int freq,int spin,int sp){
  //on
digitalWrite(spin,HIGH);
delayMicroseconds(sp*freq);

// off
digitalWrite(spin,LOW);
delayMicroseconds(sp*(254-freq));
} //spwm
*/

