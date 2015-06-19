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
  // set all rows and columns to OUTPUT and write HIGH:
  for(int i=0; i<numRows; i++){
    pinMode(rows[i], OUTPUT);
    digitalWrite(rows[i], HIGH);
  }
    for(int i=0; i<numCols; i++){
    pinMode(cols[i], OUTPUT);
    digitalWrite(cols[i], HIGH);
  }
  Serial.begin(9600);
}

void loop() {
  for(int colCount=0; colCount<numCols; colCount++){
    digitalWrite(cols[colCount], LOW);  // set LOW

    for(int rowCount=0; rowCount<numRows; rowCount++){
      pinMode(rows[rowCount], INPUT);  // set as INPUT
      delay(10);
      incomingValues[ ( (colCount)*numRows) + (rowCount)] = analogRead(rows[rowCount]);  // read INPUT
      
      // set pin back to OUTPUT, HIGH:
      pinMode(rows[rowCount], OUTPUT);
      digitalWrite(rows[rowCount], HIGH);

    }// end rowCount

  }// end colCount

  // Print the incoming values of the grid:
  for(int i=0; i<36; i++){
    Serial.print(incomingValues[i]);
    if(i<35) Serial.print(",");
  }
  Serial.println();
}













