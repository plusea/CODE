// Pink Columns = analog read = INPUT
// White Rows = digital write = OUTPUT

//test!

// We need 4 pins / multiplexer so that we can address the pin (1 of 16)
// on the multiplexer that we want to turn on.

// Columns = INPUT

// Mux 1
int oneA = 9;
int oneB = 10;
int oneC = 11;
int oneD = 12;

// Mux 2
int twoA = 8;
int twoB = 7;
int twoC = 13;
int twoD = 14;

// Read off Values from Here
int COM1 = 21;
int COM2 = 20;

// Rows = OUTPUT
// We'll use the multiplexers to apply voltage to each of their 16 pins in turn

// Mux 3
int threeA = 6;
int threeB = 5;
int threeC = 15;
int threeD = 16;

// Mux 4
int fourA = 4;
int fourB = 3;
int fourC = 2;
int fourD = 1;

// Apply voltage from here
int COM3 = 19;
int COM4 = 18;

// since not all pins of each multiplexer are connected to rows/columns on the skin
// the following arrays indicates which pins are connected, to reflect the following:
// MP1 columns connected to pins: 0-3, 8-15
// MP2 columns connected to pins: 0-15
// MP3 rows connected to pins: 0-3, 8-15
// MP4 rows connected to pins: 0-15

int colPinRef [] = {
  0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15, 0,1,2,3, 8,9,10,11,12,13,14,15};
int rowPinRef [] = {
  0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15, 0,1,2,3, 8,9,10,11,12,13,14,15};

int metaMsk[16][4] = {
  {
    0, 0, 0, 0    }
  ,
  {
    1, 0, 0, 0    }
  ,
  {
    0, 1, 0, 0    }
  ,
  {
    1, 1, 0, 0    }
  ,
  {
    0, 0, 1, 0    }
  ,
  {
    1, 0, 1, 0    }
  ,
  {
    0, 1, 1, 0    }
  ,
  {
    1, 1, 1, 0    }
  ,
  {
    0, 0, 0, 1    }
  ,
  {
    1, 0, 0, 1    }
  ,
  {
    0, 1, 0, 1    }
  ,
  {
    1, 1, 0, 1    }
  ,
  {
    0, 0, 1, 1    }
  ,
  {
    1, 0, 1, 1    }
  ,
  {
    0, 1, 1, 1    }
  ,
  {
    1, 1, 1, 1    }
};

// We will read off values one row at a time, this array will store those values
int matrixSize = 1*28;
int matrixValues[28];

// The values of these variables will be used to select the pin from multiplexers 1 and 2
// See HEF4067B Datasheet for codes (function table)
int c0 = 0;
int c1 = 0;
int c2 = 0;
int c3 = 0;
int col = 0; // storeing the bin code

// Used to select the pin from multiplexers 3 and 4
// See HEF4067B Datasheet for codes (function table)
int r0 = 0;
int r1 = 0;
int r2 = 0;
int r3 = 0;
int row = 0; // storeing the bin code

int rowCount; // just a count
int mp = 3; // for switching between multiplexers 3 and 4 during read-off


void setup(){

  // Columns = INPUT

  // Mux 1
  pinMode(oneA, OUTPUT); //A
  pinMode(oneB, OUTPUT); //B
  pinMode(oneC, OUTPUT); //C
  pinMode(oneD, OUTPUT); //D
  // Mux 2
  pinMode(twoA, OUTPUT); //A
  pinMode(twoB, OUTPUT); //B
  pinMode(twoC, OUTPUT); //C
  pinMode(twoD, OUTPUT); //D
  // Read values from here
  pinMode(COM1, INPUT);
  pinMode(COM2, INPUT);

  // ROWS = OUTPUT
  // Mux 3
  pinMode(threeA, OUTPUT); //A
  pinMode(threeB, OUTPUT); //B
  pinMode(threeC, OUTPUT); //C
  pinMode(threeD, OUTPUT); //D
  // Mux 4
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
  //ROWS - White Layer //
  ////////

  // We want to start sending power to Mux 3 + 4
  // Then we iterate over 16 pins for mux 4
  // and 12 pins for mux 3, sending power to each in turn
  // Then we want to read from 16 pins on mux 1
  // and 12 pins on mux 2

  for (int rowCount = 0; rowCount < 28; rowCount++){

    // Set 1 output to HIGH, all else to LOW
    //row = (rowCount % 16);
    r0 = metaMsk[rowPinRef[rowCount]][0];
    r1 = metaMsk[rowPinRef[rowCount]][1];
    r2 = metaMsk[rowPinRef[rowCount]][2];
    r3 = metaMsk[rowPinRef[rowCount]][3];

    // We always want to parse high through the pins on Mux 4 first, because it has all 16 pins connected
    if (rowCount < 16) {
      // Turn Off Mux 3, Turn On Mux 4
      digitalWrite(COM3, LOW);
      digitalWrite(COM4, HIGH);
      // Mux 4 - 16 outputs
      digitalWrite(fourA, r0); // A0 on Mux
      digitalWrite(fourB, r1); // A1 on Mux
      digitalWrite(fourC, r2); // A2 on Mux
      digitalWrite(fourD, r3); // A3 on Mux
    }   
    else {
      // Turn Off Mux 4, Turn On Mux 3
      digitalWrite(COM4, LOW);
      digitalWrite(COM3, HIGH);
      // Mux 3 - 12 outputs
      digitalWrite(threeA, r0); //send to Digital OUT 1
      digitalWrite(threeB, r1); //send to Digital OUT 2
      digitalWrite(threeC, r2); //send to Digital OUT 3
      digitalWrite(threeD, r3); //send to Digital OUT 4
    }

    Serial.print(rowCount);
    Serial.print(",");

    // Collect analog values off of each column

    ////////
    //COLUMNS - Pink layer
    ////////

    for (int colCount = 0; colCount < 28; colCount++) {
      //col = (colCount % 16);
      c0 = metaMsk[colPinRef[colCount]][0];
      c1 = metaMsk[colPinRef[colCount]][1];
      c2 = metaMsk[colPinRef[colCount]][2];
      c3 = metaMsk[colPinRef[colCount]][3];

      // We always want to read from Mux 2 first because it has all 16 pins connected
      if (colCount < 16) {
        // Mux 2
        digitalWrite(twoA, c0); //send to Digital OUT 1
        digitalWrite(twoB, c1); //send to Digital OUT 2
        digitalWrite(twoC, c2); //send to Digital OUT 3
        digitalWrite(twoD, c3); //send to Digital OUT 4
        matrixValues[colCount] = analogRead(COM2);
      }
      else {
        // Mux 1
        digitalWrite(oneA, c0); //send to Digital OUT 1
        digitalWrite(oneB, c1); //send to Digital OUT 2
        digitalWrite(oneC, c2); //send to Digital OUT 3
        digitalWrite(oneD, c3); //send to Digital OUT 4
        matrixValues[colCount] = analogRead(COM1);
      } 

    }//end for

    // Print out the values from the Row we've just filled
    for (int i=0; i<28; i++){
      Serial.print(matrixValues[i], DEC);
      if (i < matrixSize - 1) Serial.print(",");
    }
    // Newline
    Serial.println();
    delay(10);
  }
}//end loop


