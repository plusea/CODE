// TILT SENSING QUILT CODE 

int r0 = 0;      //value select pin at the 4051 (s0) 
int r1 = 0;      //value select pin at the 4051 (s1) 
int r2 = 0;      //value select pin at the 4051 (s2) 
int ROWcode = 0;     // storeing the bin code 
int c0 = 0;      //value select pin at the 4051 (s0) 
int c1 = 0;      //value select pin at the 4051 (s1) 
int c2 = 0;      //value select pin at the 4051 (s2) 
int COLcode = 0;     // storeing the bin code 
int ROWcount = 0;    // just a count 
int COLcount = 0;    // just a count 
int  ROWbin [] = {
  000, 1, 10, 11, 100, 101, 110, 111};//bin = binar, some times it is so easy 
int  COLbin [] = {
  000, 1, 10, 11, 100, 101, 110, 111};//bin = binar, some times it is so easy 
int controlPinROW1 = 4;  //A
int controlPinROW2 = 3;  //B
int controlPinROW3 = 2;  //C
int controlPinCOL1 = 10;  //A
int controlPinCOL2 = 9;  //B
int controlPinCOL3 = 8;  //C
int ROWpin = 1;  //COM1
int COLpin = 12;  //COM2

int sensorIN = 0;


void setup() { 
  pinMode(controlPinROW1, OUTPUT);    // s0 
  pinMode(controlPinROW2, OUTPUT);    // s1 
  pinMode(controlPinROW3, OUTPUT);    // s2 
  pinMode(controlPinCOL1, OUTPUT);    // s0 
  pinMode(controlPinCOL2, OUTPUT);    // s1 
  pinMode(controlPinCOL3, OUTPUT);    // s2 
  //digitalWrite(14, HIGH);   
  digitalWrite(15, HIGH);
  pinMode(COLpin, OUTPUT);
  digitalWrite(COLpin, LOW);
  
  
  Serial.begin(9600); 
} 



void loop () { 
    multi();
}



void multi() {

  for (COLcount=0; COLcount<8; COLcount++) { 
    COLcode = COLbin[COLcount];      
    c0 = COLcode & 0x01; 
    c1 = (COLcode>>1) & 0x01; 
    c2 = (COLcode>>2) & 0x01;  

    digitalWrite(controlPinCOL1, c0); 
    digitalWrite(controlPinCOL2, c1); 
    digitalWrite(controlPinCOL3, c2); 

    

    for (ROWcount=0; ROWcount<8; ROWcount++) { 
      ROWcode = ROWbin[ROWcount];      
      r0 = ROWcode & 0x01; 
      r1 = (ROWcode>>1) & 0x01; 
      r2 = (ROWcode>>2) & 0x01;

      digitalWrite(controlPinROW1, r0); 
      digitalWrite(controlPinROW2, r1); 
      digitalWrite(controlPinROW3, r2); 



      sensorIN = analogRead(ROWpin);

      Serial.print(sensorIN, DEC);    // print its value out as an ASCII numeric string
      if ((COLcount+1) * (ROWcount+1) < 63) Serial.print(",");    // if this isn't the last sensor to read then print a comma after it

    }  //end for ROWs
  }  //end for COLs

  Serial.println();  // after all the sensors have been read print a newline and carriage return
  //delay(1);
}






void test() {

}


