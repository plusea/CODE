int sensorPin = 2;
int LED0 = 0;
int LED1 = 1;
int LED2 = 2;

int count = 0;
int state = 0;
int reading;

int threshold = 850;

void setup()
{
  pinMode(sensorPin, INPUT);
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(4, HIGH);
  digitalWrite(LED0, HIGH);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  //  Serial.begin(9600);
}

void loop()
{
  reading = analogRead(sensorPin);
  //Serial.println(reading);
  if(reading < threshold && state == 0){
    count++;
    state=1;
  }

  if(count == 1) {
    digitalWrite(LED0, HIGH);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  }

  if(count == 2) {
    digitalWrite(LED0, LOW);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
  }

  if(count == 3) {
    digitalWrite(LED0, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
  }

  if(count == 4) {
    digitalWrite(LED0, HIGH);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
  }

  if(count == 4) count = 0;

  if(reading > threshold) state = 0;   

  delay(10);
}












