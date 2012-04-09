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

int sinetable[64] = { // http://en.wikipedia.org/wiki/Lookup_table
5,
5,
6,
6,
7,
7,
8,
8,
9,
9,
9,
9,
10,
10,
10,
10,
10,
10,
10,
10,
10,
9,
9,
9,
9,
8,
8,
7,
7,
6,
6,
5,
5,
5,
4,
4,
3,
3,
2,
2,
1,
1,
1,
1,
0,
0,
0,
0,
0,
0,
0,
0,
0,
1,
1,
1,
1,
2,
2,
3,
3,
4,
4,
5};

//5000 is about one second...
//int count[]={-5000,-7000,-10000,-12000,-15000,-17000,-20000,-22000,-25000,-27000,-30000};
//immedi-start
int count[]={0,0,0,0,0,0,0,0,0,0,0};

//double time[]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

//constant
double frequency[]= {0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02};

//constant * 2
//double frequency[]= {0.04, 0.04, 0.04, 0.02, 0.02, 0.02, 0.04, 0.04, 0.04, 0.02, 0.02, 0.02};

//null
//double frequency[]= {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

//bell-curve-ish
//double frequency[]= {0.01, 0.02, 0.02, 0.04, 0.04, 0.04, 0.08, 0.04, 0.04, 0.02, 0.02, 0.01};



//ramp up subtle
//double frequency[]= {0.01, 0.015, 0.02, 0.025, 0.03, 0.035, 0.04, 0.045, 0.05, 0.055, 0.06, 0.065};

//ramp up
//double frequency[]= {0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.1, 0.11, 0.12};

//ramp up * 2
//double frequency[]= {0.02, 0.04, 0.06, 0.08, 0.1, 0.12, 0.14, 0.16, 0.18, 0.2, 0.22, 0.24};


//0x
//const double fDelay[]= {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//1x
//const double fDelay[]= {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
//2x
//const double fDelay[]= {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24};
// 3x
const double fDelay[]= {3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36};
// 4x
//const double fDelay[]= {4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48};
// 5x
//const double fDelay[]= {5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60};

//const double fDelay[]= {0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44};
//const double fDelay[]= {0, 4, 2, 8, 5, 12, 10, 24, 20, 48, 40, 96};

float fAmp=1.0;
double acc=0.0;

int arousalPin= 4;
int arousalValue = 0;
int pushDebounce=10;
int upDown=1;

void setup(){

  pinMode(4,INPUT);
  digitalWrite(4, HIGH); 
}





void loop(){

  
  arousalValue = analogRead(2);
  if (arousalValue < 400 && arousalValue > 0 ){
        upDown=1;
    if (arousalValue < 100){
        upDown=-1;
        fAmp=1.0;  
    }
  }
    arousalValue=0;


  fAmp+=0.0001;
//  fDelay[4]+=0.01;
    


for (int i=0;i<12;i++){
      
    //demo mode!
    //i = int(millis() * 0.001)%12;

    //0-255
    //int fade=1+ sinetable[int(millis()*frequency[i] + fDelay[i])%32];
    //0-1
    //fade= fade/255.0;
  
   if (count[i]>0){
   
    if (count[i]%int(1+ sinetable[int(millis() * fAmp * frequency[i] + fDelay[i])%64])==0){
      digitalWrite(setPinMode(i+1),HIGH);
      count[i]=1;
      }
    else{
      digitalWrite(setPinMode(i+1),LOW);
      }
   }
    count[i]+=upDown;

  if (count[i]<0)
    count[i]=0;
    
  }

}



int setPinMode(int led){

  switch (led){
    // 1
  case 1:
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  digitalWrite(0, LOW);
  return 1;
  
    // 2
  case 2:
  pinMode(0, OUTPUT);
  pinMode(1, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
  digitalWrite(0, LOW);
  return 2;

  // 3
  case 3:
  pinMode(0, INPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
  digitalWrite(0, LOW);
  return 3;

  // 4
  case 4:
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  digitalWrite(1, LOW);
  return 0;

  // 5
  case 5:
  pinMode(0, INPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
  digitalWrite(1, LOW);
  return 2;
    // 6
  case 6:
  pinMode(0, INPUT);
  pinMode(1, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  digitalWrite(1, LOW);
  return 3;
  
  // 7
  case 7:
  pinMode(0, OUTPUT);
  pinMode(1, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
  digitalWrite(2, LOW);
  return 0;
  
  // 8
  case 8:
  pinMode(0, INPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
  digitalWrite(2, LOW);
  return 1;
  
  // 9
  case 9:
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(2, LOW);
  return 3;

  // 10
  case 10:
  pinMode(0, OUTPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  return 0;

    // 11
  case 11:
  pinMode(0, INPUT);
  pinMode(1, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  return 1;
  
      // 12
  case 12:
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  return 2;
  }
  
}
