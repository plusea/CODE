// ROWS = digital write
// COLS = analog read

int Ac = 8;
int Bc = 9;
int Cc = 10;
int Dc = 11;

int Ar = 4;
int Br = 5;
int Cr = 6;
int Dr = 7;

int COMc = A0;
int COMr = 15;

//int bin [] = {0000, 1000, 0100, 1100, 0010, 1010, 0110, 1110, 0001, 1001, 0101, 1101, 0011, 1011, 0111, 1111};
int bin [] = {
  1010, 0110, 1110, 0001, 1001, 0101, 1101, 0011, 1011, 0111, 1111};
int matrixValues[11*11];
int r0 = 0;      //value select pin at the 4051 (s0) 
int r1 = 0;      //value select pin at the 4051 (s1) 
int r2 = 0;      //value select pin at the 4051 (s2) 
int r3 = 0;      //value select pin at the 4051 (s3) 
int row = 0;     // storeing the bin code 
int c0 = 0;      //value select pin at the 4051 (s0) 
int c1 = 0;      //value select pin at the 4051 (s1) 
int c2 = 0;      //value select pin at the 4051 (s2) 
int c3 = 0;      //value select pin at the 4051 (s3) 
int col = 0;     // storeing the bin code 
int rowCount;    // just a count 
int numRows = 11;
int numCols = 11;



void setup(){ 
  pinMode(Ac, OUTPUT); //A
  pinMode(Bc, OUTPUT); //B
  pinMode(Cc, OUTPUT); //C
  pinMode(Dc, OUTPUT); //D
    pinMode(Ar, OUTPUT); //A
  pinMode(Br, OUTPUT); //B
  pinMode(Cr, OUTPUT); //C
  pinMode(Dr, OUTPUT); //D
  pinMode(COMc, INPUT);
  //digitalWrite(14, HIGH);//pullup
  pinMode(COMr, OUTPUT);

  Serial.begin(9600); 
}//end setup






void loop () { 

  ////////
  //ROWS//
  ////////
  
  //set one digital output to LOW, all else to HIGH
    row = bin[rowCount];      
    
    r0 = row & 0x01; 
    r1 = (row>>1) & 0x01; 
    r2 = (row>>2) & 0x01; 
    r3 = (row>>3) & 0x01; 

    digitalWrite(Ar, r0); //send to Digital OUT 1
    digitalWrite(Br, r1); //send to Digital OUT 2
    digitalWrite(Cr, r2); //send to Digital OUT 3
    digitalWrite(Dr, r3); //send to Digital OUT 4
    
    digitalWrite(COMr, HIGH);

Serial.print(rowCount + "\t");

  ////////
  //COLS//
  ////////
  
  for (int count = 0; count < numCols; count++) { 
    col = bin[count];      
    c0 = col & 0x01; 
    c1 = (col>>1) & 0x01; 
    c2 = (col>>2) & 0x01; 
    c3 = (col>>3) & 0x01; 

    digitalWrite(Ac, r0); //send to Digital OUT 1
    digitalWrite(Bc, r1); //send to Digital OUT 2
    digitalWrite(Cc, r2); //send to Digital OUT 3
    digitalWrite(Dc, r3); //send to Digital OUT 4

    delay(10);

    matrixValues[count*rowCount] = analogRead(COMc);

    Serial.print(matrixValues[count*rowCount] + "\t");
  }//end for

  Serial.println("");

  rowCount++;

  if(rowCount > numRows){
    rowCount = 0;
    delay(100);
  }

}//end loop





