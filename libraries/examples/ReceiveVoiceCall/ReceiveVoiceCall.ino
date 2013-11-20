/*
 Receive Voice Call
 
 This sketch, for the Arduino GSM shield, receives voice calls, 
 displays the calling number, waits a few seconds and gently hangs,
 
 Circuit:
 * GSM shield 
 * Voice circuit. 
 With no voice circuit the call will send nor receive any sound
  
 created Mar 2012
 by Javier Zorzano
 
 This example is in the public domain.
 */

// libraries
#include <GSM.h>

// PIN Number
#define PINNUMBER ""

// initialize the library instance
GSM gsmAccess; // include a 'true' parameter for debug enabled
GSMVoiceCall vcs;


char numtel[20];           // buffer for the incoming call

void setup()
{
  // initialize serial communications
  Serial.begin(9600);
  Serial.println("Receive Voice Call");
  
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
  
  // This makes sure the modem notifies correctly incoming events
  vcs.hangCall();
  
  Serial.println("Waiting Call");
}

void loop()
{
  // Check the status of the voice call
  switch (vcs.getvoiceCallStatus()) 
  {
    case IDLE_CALL: // Nothing is happening
      
      break;
      
    case CALLING: // This should never happen, as we are not placing a call
      
      Serial.println("CALLING");
      break;
      
    case RECEIVINGCALL: // Yes! Someone is calling us
      
      Serial.println("RECEIVING CALL");
      
      // Retrieve the calling number
      vcs.retrieveCallingNumber(numtel, 20);
      
      // Print the calling number
      Serial.print("Number:");
      Serial.println(numtel);
      
      // Answer the call, establish the call
      vcs.answerCall();         
      break;
      
    case TALKING:  // In this case the call would be established
      
      Serial.println("TALKING. Enter line to interrupt.");
      while(Serial.read()!='\n')
        delay(100);
      vcs.hangCall();
      Serial.println("HANG. Waiting Call.");      
      break;
  }
  delay(1000);
}


