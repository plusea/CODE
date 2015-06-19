/*
 square of eeonyx fabric with 6 conductive rows and 6 conductive columns
 parsing through this grid by switching individual rows/columns to be 
 HIGH, LOW or INPUT (high impedance) to detect location and pressure
 >> http://howtogetwhatyouwant.at/
 */

#define numRows 6
#define numCols 6
int rows[] = { 
  A0, A1, A2, A3, A4, A5, A6 };   
int cols[] = { 
  2,3,4,5,6,7};  
int incomingValues[36] = {
};   


void setup() {
  // set all rows and columns to INPUT (high impedance):
  for(int i=0; i<numRows; i++){
    pinMode(rows[i], INPUT);
  }
    for(int i=0; i<numCols; i++){
    pinMode(cols[i], INPUT);
  }
  Serial.begin(9600);
}

void loop() {
  for(int colCount=0; colCount<numCols; colCount++){
    pinMode(cols[colCount], OUTPUT);  // set as OUTPUT
    digitalWrite(cols[colCount], LOW);  // set LOW

    for(int rowCount=0; rowCount<numRows; rowCount++){
      pinMode(rows[rowCount], INPUT_PULLUP);  // set as INPUT with PULLUP RESISTOR
      delay(1);
      incomingValues[ ( (colCount)*numRows) + (rowCount)] = analogRead(rows[rowCount]);  // read INPUT
      
      // set pin back to INPUT
      pinMode(rows[rowCount], INPUT);

    }// end rowCount

    pinMode(cols[colCount], INPUT);  // set back to INPUT!

  }// end colCount

  // Print the incoming values of the grid:
  for(int i=0; i<36; i++){
    Serial.print(incomingValues[i]);
    if(i<35) Serial.print(",");
  }
  Serial.println();
}













