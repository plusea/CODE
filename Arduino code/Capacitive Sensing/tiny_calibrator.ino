
// tinytuner

#include <SoftwareSerial.h>

SoftwareSerial mySerial(1, 4); // RX, TX

void setup()  
{
  pinMode(0,OUTPUT);
  pinMode(2,OUTPUT);
  delay(2000);

  mySerial.begin(9600);

  for (int i=0; i<256; ++i) {
    OSCCAL  = i;
    delay(1);
    mySerial.println();
    mySerial.print("OSCCAL=");
    mySerial.print(i);
   // delay(5);

    if( i<50)
    {
      digitalWrite(0,HIGH);
      digitalWrite(2,HIGH);
    }
    else if( i< 100)
    {
      digitalWrite(0,LOW);
      digitalWrite(2,LOW);
    }
    else if( i<150)
    {
      digitalWrite(0,HIGH);
      digitalWrite(2,LOW);
    }
    else
    {
      digitalWrite(2,HIGH);
      digitalWrite(0,LOW);
    }
  }
  while(1)
  {
    digitalWrite(0, HIGH);
    digitalWrite(2, HIGH);
    delay(250);
    digitalWrite(0, LOW);
    digitalWrite(2, LOW);
    delay(250);  
  }
}

void loop() // run over and over
{

}


