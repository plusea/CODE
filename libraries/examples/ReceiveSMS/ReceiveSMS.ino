/*
SMS receiver
 
 This sketch, for the Arduino GSM shield, waits for SMS messages 
 and displays them through the Serial port. 
 
 Circuit:
 * GSM shield 
 
 created 25 Feb 2012
 by Javier Zorzano / TD
 
 This example is in the public domain.
*/

// libraries
#include <GSM.h>

// PIN Number
#define PINNUMBER ""

// initialize the library instance
GSM gsmAccess; // include a 'true' parameter for debug enabled
GSM_SMS sms;

char remoteNumber[20];  // Holds the emitting number

void setup() 
{
  // initialize serial communications
  Serial.begin(9600); 

  Serial.println("SMS Messages Receiver");
    
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
  Serial.println("Waiting for messages");
}

void loop() 
{
  char c;
  
  // If there are any SMSs available()  
  if (sms.available())
  {
    Serial.println("Message received from:");
    
    // Get remote number
    sms.remoteNumber(remoteNumber, 20);
    Serial.println(remoteNumber);

    // This is just an example of message disposal    
    // Messages starting with # should be discarded
    if(sms.peek()=='#')
    {
      Serial.println("Discarded SMS");
      sms.flush();
    }
    
    // Read message bytes and print them
    while(c=sms.read())
      Serial.print(c);
      
    Serial.println("\nEND OF MESSAGE");
    
    // delete message from modem memory
    sms.flush();
    Serial.println("MESSAGE DELETED");
  }

  delay(1000);

}


