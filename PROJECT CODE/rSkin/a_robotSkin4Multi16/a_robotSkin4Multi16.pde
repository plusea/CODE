// WHITE ROWS = analog read = INPUT
// PINK COLUMNS = digital write = OUTPUT

// ROWS = INPUT
int oneA = 9;
int oneB = 10;
int oneC = 11;
int oneD = 12;

int twoA = 8;
int twoB = 7;
int twoC = 13;
int twoD = 14;

int COM1 = A0;//21
int COM2 = A1;//20

// COLS = OUTPUT
int threeA = 6;
int threeB = 5;
int threeC = 15;
int threeD = 16;

int fourA = 4;
int fourB = 3;
int fourC = 2;
int fourD = 1;

int COM3 = 19;//19
int COM4 = 18;//18

int bin [] = {
  0000, 1000, 0100, 1100, 0010, 1010, 0110, 1110, 0001, 1001, 0101, 1101, 0011, 1011, 0111, 1111};

int matrixSize = 28*28;
int matrixValues[784];

int r0 = 0;      //value select pin at the 4051 (s0) 
int r1 = 0;      //value select pin at the 4051 (s1) 
int r2 = 0;      //value select pin at the 405 (s2) 
int r3 = 0;      //value select pin at the 4051 (s3) 
int row = 0;     // storeing the bin code 

int c0 = 0;      //value select pin at the 4051 (s0) 
int c1 = 0;      //value select pin at the 4051 (s1) 
int c2 = 0;      //value select pin at the 4051 (s2) 
int c3 = 0;      //value select pin at the 4051 (s3) 
int col = 0;     // storeing the bin code 

int colCount;    // just a count 
int mp = 3;  // for switching between multiplexers 3 and 4


void setup(){ 

  // COLUMNS = INPUT
  pinMode(oneA, OUTPUT); //A
  pinMode(oneB, OUTPUT); //B
  pinMode(oneC, OUTPUT); //C
  pinMode(oneD, OUTPUT); //D

  pinMode(twoA, OUTPUT); //A
  pinMode(twoB, OUTPUT); //B
  pinMode(twoC, OUTPUT); //C
  pinMode(twoD, OUTPUT); //D

  pinMode(COM1, INPUT);
  pinMode(COM2, INPUT);

  //digitalWrite(21, HIGH);//pullup
  //digitalWrite(120, HIGH);//pullup

  // ROWS = OUTPUT
  pinMode(threeA, OUTPUT); //A
  pinMode(threeB, OUTPUT); //B
  pinMode(threeC, OUTPUT); //C
  pinMode(threeD, OUTPUT); //D

  pinMode(fourA, OUTPUT); //A
  pinMode(fourB, OUTPUT); //B
  pinMode(fourC, OUTPUT); //C
  pinMode(fourD, OUTPUT); //D

  pinMode(COM3, OUTPUT);
  pinMode(COM4, OUTPUT);

  Serial.begin(9600); 

}//end setup









void loop () { 

  ////////
  //COLS//
  ////////

  //set 1 digital output to HIGH, all else to LOW
  col = bin[colCount];      
  c0 = col & 0x01; 
  c1 = (col>>1) & 0x01; 
  c2 = (col>>2) & 0x01; 
  c3 = (col>>3) & 0x01; 

  digitalWrite(threeA, r0); //send to Digital OUT 1
  digitalWrite(threeB, r1); //send to Digital OUT 2
  digitalWrite(threeC, r2); //send to Digital OUT 3
  digitalWrite(threeD, r3); //send to Digital OUT 4

  digitalWrite(fourA, r0); //send to Digital OUT 1
  digitalWrite(fourB, r1); //send to Digital OUT 2
  digitalWrite(fourC, r2); //send to Digital OUT 3
  digitalWrite(fourD, r3); //send to Digital OUT 4

  if(mp == 3) {
    digitalWrite(COM3, HIGH);
    digitalWrite(COM4, LOW);
  }
  if(mp == 4) {
    digitalWrite(COM3, LOW);
    digitalWrite(COM4, HIGH);
  }

  Serial.print(colCount);
  Serial.print("\t");



  ////////
  //ROWS//
  ////////

  for (int rowCount = 0; rowCount < 16; rowCount++) { 
    row = bin[rowCount];      
    r0 = row & 0x01; 
    r1 = (row>>1) & 0x01; 
    r2 = (row>>2) & 0x01; 
    r3 = (row>>3) & 0x01; 

    digitalWrite(oneA, r0); //send to Digital OUT 1
    digitalWrite(oneB, r1); //send to Digital OUT 2
    digitalWrite(oneC, r2); //send to Digital OUT 3
    digitalWrite(oneD, r3); //send to Digital OUT 4

    digitalWrite(twoA, r0); //send to Digital OUT 1
    digitalWrite(twoB, r1); //send to Digital OUT 2
    digitalWrite(twoC, r2); //send to Digital OUT 3
    digitalWrite(twoD, r3); //send to Digital OUT 4

    matrixValues[colCount * rowCount] = analogRead(COM1);
    matrixValues[16 + colCount * rowCount] = analogRead(COM2);

    //Serial.print(matrixValues[colCount * rowCount]);
    //Serial.print("\t");
    //Serial.print(matrixValues[16 + colCount * rowCount]);
    //Serial.print("\t");
  }//end for

  colCount++;

  if(colCount >= 16){
    if(mp==3) mp=4;
    if(mp==4) mp=3;
    colCount = 0;
    //delay(100);
  }

  for (int i=0; i<784; i++){
    Serial.print(matrixValues[i], DEC);
    if (i < matrixSize - 1) Serial.print(",");
    //if(i % 28 == 0) Serial.println();
  }
  Serial.println();
  //delay(1000);

}//end loop









