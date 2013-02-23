// read analog inputs and send data


#define ledBlue 6
#define ledRed 5
int analog0 = A7;
int analog1 = A6;
int analog2 = A0;
int analog3 = A1;
int analog4 = A2;
int analog5 = A3;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.

  pinMode(ledBlue, OUTPUT);     
  pinMode(ledRed, OUTPUT); 
Serial.begin(9600);  
}

// the loop routine runs over and over again forever:
void loop() {
  //testBlink();
  testRead();

}

void testRead(){
analog0 = analogRead(A0);
analog1 = analogRead(A1);
Serial.println(analog0 + "//" + analog1);
}


void testBlink(){
  digitalWrite(ledBlue, HIGH);
  digitalWrite(ledRed, LOW);
  delay(1000);
  digitalWrite(ledBlue, LOW);
  digitalWrite(ledRed, HIGH);
  delay(1000);
  }

