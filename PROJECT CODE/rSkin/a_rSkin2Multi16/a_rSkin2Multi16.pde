// ROWS = digital write
// COLS = analog read

int colPins[] = {
  11,10,9,8};
int rowPins[] = {
  7,6,5,4};

int COMc = A0;
int COMr = 19;

// the numbers in here represent the pin numbers on the multiplexer to which the skin is actually connected, 
// and they refer back to the position in the bin array:
int colRef [] = {
  8,9,10,11,12,5,4,3,2,1,0};  
int rowRef [] = {
  8,9,10,11,12,5,4,3,2,1,0};

int multiChannel[16][4]={
  {
    0,0,0,0  }
  , //channel 0
  {
    1,0,0,0  }
  , //channel 1
  {
    0,1,0,0  }
  , //channel 2
  {
    1,1,0,0  }
  , //channel 3
  {
    0,0,1,0  }
  , //channel 4
  {
    1,0,1,0  }
  , //channel 5
  {
    0,1,1,0  }
  , //channel 6
  {
    1,1,1,0  }
  , //channel 7
  {
    0,0,0,1  }
  , //channel 8
  {
    1,0,0,1  }
  , //channel 9
  {
    0,1,0,1  }
  , //channel 10
  {
    1,1,0,1  }
  , //channel 11
  {
    0,0,1,1  }
  , //channel 12
  {
    1,0,1,1  }
  , //channel 13
  {
    0,1,1,1  }
  , //channel 14
  {
    1,1,1,1  }  //channel 15
};

const int numRows = 11;
const int numCols = 11;
const int matrixSize = numRows*numCols;
int matrixValues[matrixSize];
int rowCount;    // just a count
int colCount;    // just a count


void setup(){ 
  for(int i = 0; i < 4; i ++){
    pinMode(colPins[i], OUTPUT);  // sets A,B,C,D as output
    pinMode(rowPins[i], OUTPUT);  // sets A,B,C,D as output
  }
  pinMode(COMc, INPUT); // don't forget external pull-up resistor!
  pinMode(COMr, OUTPUT);
  digitalWrite(COMr, HIGH);
  //Serial.begin(9600); 
  Serial.begin(115200); 
} //end setup


void loop () { 
  //ROWS//
  for(int r = 0; r < 4; r ++){
    digitalWrite(rowPins[r], multiChannel[rowRef[rowCount]][r]);
  }
  //Serial.print(rowCount);
  //Serial.print("\t");

  //COLS//
  for (int colCount = 0; colCount < numCols; colCount++) { 
    for(int c = 0; c < 4; c ++){
      digitalWrite(colPins[c], multiChannel[colRef[colCount]][c]);
    }
    matrixValues[(rowCount*numRows)+colCount] = analogRead(COMc);
    //Serial.print((rowCount*numRows)+colCount);
    //Serial.print(" : ");
    Serial.print(matrixValues[(rowCount*numRows)+colCount]);
    if((rowCount*numRows)+colCount < matrixSize - 1) Serial.print(",");
    //Serial.print("\t");
  }//end for

  rowCount++;
  if(rowCount == numRows){
    rowCount = 0;
    Serial.println();
  }
  
  delay(5); // this delay keeps the processing application from jumping around. most likely missing the line breaks.

}//end loop








