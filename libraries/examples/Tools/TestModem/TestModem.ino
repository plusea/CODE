/*
 
 This example test if your modem is working correctly.
 
 Circuit:
 * GSM shield attached (
 
 Created 12 Jun 2012
 by David del Peral
 */

// libraries
#include <GSM.h>

// modem verification object
GSMModem modemTest;

// IMEI variable
String IMEI = "";

// serial monitor result messages
String oktext = "OK";
String errortext = "ERROR";

void setup()
{
  // initialize serial communications
  Serial.begin(9600);
  
  // start modem test (reset and check response)
  Serial.print("Starting modem test...");
  if(modemTest.begin())
    Serial.println(oktext);
  else
    Serial.println("ERROR, no modem answer.");
}

void loop()
{
  // get modem IMEI
  Serial.print("Checking IMEI...");
  IMEI = modemTest.getIMEI();
  
  // check IMEI responsed
  if(IMEI != NULL)
  {
    Serial.println(oktext);
    // show IMEI in serial monitor
    Serial.println("Modem's IMEI: " + IMEI);
    // reset modem for check booting
    Serial.print("Reseting modem...");
    modemTest.begin();
    // get and check IMEI one more time
    if(modemTest.getIMEI() != NULL)
    {
      Serial.println(oktext);
      Serial.println("TEST COMPLETE!");
    }
    else
    {
      Serial.println(errortext);
    }
  }
  else
  {
    Serial.println(errortext);
  }
  while(true);
}

