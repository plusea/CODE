int A = 6;
int B = 7;
int C = 8;
int COM = A0;
int a,b,c;

int multiMask [] = {
  2,0,6,7,4,3,5,1};

int multi[8][3] = {
  {
    0,0,0},
  {
    0,0,1 }
  ,
  {
    0,1,0}
  ,
  {
    0,1,1}
  ,
  {
    1,0,0}
  ,
  {
    1,0,1}
  ,
  {
    1,1,0}
  ,
  {
    1,1,1}
};

void setup() {
  
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(9, LOW);  //GND
  digitalWrite(10, HIGH);  //VCC
  digitalWrite(5, LOW);  //GND
  digitalWrite(13, LOW);  //GND
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(COM, INPUT);
  //digitalWrite(14, HIGH);
  Serial.begin(9600);
  }

void loop() {
  
  for (int count = 0; count < 8; count++){
    a = multi[multiMask[count]][0];
    b = multi[multiMask[count]][1];
    c = multi[multiMask[count]][2];
    digitalWrite(A, a);
    digitalWrite(B, b);
    digitalWrite(C, c);
    Serial.print(analogRead(COM));
    if(count<7)Serial.print(","); 
    //Serial.print("\t"); 
    //delay(500);
    }

Serial.println();
delay(100);
}


void test(){
    for(int i=0; i<10; i++){
      Serial.print(i);
      Serial.print("\t");
      Serial.print("OPEN");
      delay(500);
      Serial.print(" 1 ");
      delay(500);
      Serial.print(" 2 ");
      delay(500);
      Serial.print(" 3:\t");
      delay(500);
      Serial.print(analogRead(A2));
      Serial.print("\t");
      Serial.println(analogRead(A3));
      delay(500);
      Serial.print(i);
      Serial.print("\t");
      Serial.print("FIST");
      delay(500);
      Serial.print(" 1 ");
      delay(500);
      Serial.print(" 2 ");
      delay(500);
      Serial.print(" 3:\t");
      delay(500);
      Serial.print(analogRead(A2));
      Serial.print("\t");
      Serial.println(analogRead(A3));
      delay(500);
    }
}


