// code for thermochromic pixel output on an ATtiny85

int LED0 = 0;
int LED1 = 1;
int LED2 = 2;
int delayAmountON = 1500;
int delayAmountOFF = 6000;
int sensorPin = 2;
int value;

void setup()
{
  pinMode(sensorPin, INPUT);
  digitalWrite(4, HIGH);
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED0, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
}

void loop() {
  //value = analogRead(sensorPin);
  digitalWrite(LED0, HIGH);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  delay(delayAmountON);
  digitalWrite(LED0, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  delay(delayAmountOFF);
  digitalWrite(LED0, LOW);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  delay(delayAmountON);
  digitalWrite(LED0, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  delay(delayAmountOFF);
  digitalWrite(LED0, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  delay(delayAmountON);
  digitalWrite(LED0, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  delay(delayAmountOFF);
  /*
  digitalWrite(LED1, HIGH);
   delay(10000/8);
   
   for(int i=0; i<10; i++){
   digitalWrite(LED1, LOW);
   delay(1000/8);
   digitalWrite(LED1, HIGH);
   delay(1000/8);
   }
   
   digitalWrite(LED1, LOW);
   delay(10000/8);
   
   
   
   
   digitalWrite(LED0, HIGH);
   digitalWrite(LED1, LOW);
   digitalWrite(LED2, LOW);
   delay(delayAmount);
   digitalWrite(LED0, LOW);
   digitalWrite(LED1, HIGH);
   digitalWrite(LED2, LOW);
   delay(delayAmount);
   digitalWrite(LED0, LOW);
   digitalWrite(LED1, HIGH);
   digitalWrite(LED2, LOW);
   delay(delayAmount);
   */
} 		  








