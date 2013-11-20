/*
SMS sender
 
 This sketch, for the Arduino GSM shield,sends an SMS message 
 that you send it through the serial monitor. To make it work, 
 open the serial monitor, and when you see the READY message, 
 type a message to send. Make sure the serial monitor is set
 to send a newline when you press return.
 
 Circuit:
 * GSM shield 
 
 created 25 Feb 2012
 by Tom Igoe
 
 This example is in the public domain.
 */

// libraries
#include <GSM.h>

#define PINNUMBER ""

// initialize the library instance
GSM gsmAccess; // include a 'true' parameter for debug enabled
GSM_SMS sms;

void setup()
{
  // initialize serial communications
  Serial.begin(9600);
  
  Serial.println("SMS Messages Sender");

  // connection state
  boolean notConnected = true;

  // Start GSM shield
  // If your SIM has PIN, pass it as a parameter of begin() in quotes
  while(notConnected)
  {
    if(gsmAccess.begin(PINNUMBER)==GSM_READY)
      notConnected = false;
    else
    {
      Serial.println("Not connected");
      delay(1000);
    }
  }
  
  Serial.println("GSM initialized");
}

void loop()
{

  Serial.print("Enter a mobile number: ");
  char remoteNumber[20];  // telephone number to send sms
  readSerial(remoteNumber);
  Serial.println(remoteNumber);
    
  // sms text
  Serial.print("Now, enter SMS content: ");
  char txtMsg[200];
  readSerial(txtMsg);
  Serial.println("SENDING");
  Serial.println();
  Serial.println("Message:");
  Serial.println(txtMsg);
  
  // send the message
  sms.beginSMS(remoteNumber);
  sms.print(txtMsg);
  sms.endSMS(); 
  Serial.println("\nCOMPLETE!\n");
}

/*
  Read input serial
 */
int readSerial(char result[])
{
  int i = 0;
  while(1)
  {
    while (Serial.available() > 0)
    {
      char inChar = Serial.read();
      if (inChar == '\n')
      {
        result[i] = '\0';
        Serial.flush();
        return 0;
      }
      if(inChar!='\r')
      {
        result[i] = inChar;
        i++;
      }
    }
  }
}
