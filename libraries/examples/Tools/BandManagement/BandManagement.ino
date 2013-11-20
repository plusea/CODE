/*
 Band Management
 
 This sketch, for the Arduino GSM shield, checks the band
 currently configured in the modem and allows you to change 
 it.
 
 Please check http://www.worldtimezone.com/gsm.html
 Usual configurations:
 Europe, Africa, Middle East: E-GSM(900)+DCS(1800)
 USA, Canada, South America: GSM(850)+PCS(1900)
 Mexico: PCS(1900)
 Brazil: GSM(850)+E-GSM(900)+DCS(1800)+PCS(1900)
 
 
 Circuit:
 * GSM shield 
 
 created 12 June 2012
 by Javier Zorzano
 
 This example is in the public domain.
 */

// libraries
#include <GSM.h>

// initialize the library instance
GSMBand bandManager;

void setup()
{
  // initialize serial communications
  Serial.begin(9600);
  
  // Beginning the band manager restarts the modem
  Serial.println("Restarting modem...");
  bandManager.begin();
  Serial.println("Modem restarted.");
  
};


void loop()
{
  // Get current band  
  GSM3GSMBand band;

  band=bandManager.getBand();

  // Get and print bands printable name
  Serial.print("Current band: ");
  Serial.println(bandManager.getBandName(band));
  
  // If we have no clue on the band value, stop there.
  if(band==UNDEFINED)
    while(true);
  
  // Ask user for new band to configure
  GSM3GSMBand newBand;
  newBand=askUserBand();

  // Send command to modem to change band
  if(newBand!=UNDEFINED)
  {
    String command;
    // Tell the user what we are about to do...
    Serial.print("\nConfiguring band ");
    Serial.println(bandManager.getBandName(newBand));
    
    // Change the band
    bool operationSuccess;
    operationSuccess=bandManager.setBand(newBand);    
    
    // Tell the user if the operation was OK
    if(operationSuccess)
      Serial.println("Success");
    else
      Serial.println("Error while changing band");
  }
}

// This function offers the user different options
// through the Serial interface
// The user selects one
GSM3GSMBand askUserBand()
{
  GSM3GSMBand result;
  Serial.println("Select band:");

  // Print the different options
  Serial.print("1 ");
  Serial.println(bandManager.getBandName(EGSM_MODE));
  Serial.print("2 ");
  Serial.println(bandManager.getBandName(DCS_MODE));
  Serial.print("3 ");
  Serial.println(bandManager.getBandName(PCS_MODE));
  Serial.print("4 ");
  Serial.println(bandManager.getBandName(EGSM_DCS_MODE));
  Serial.print("5 ");
  Serial.println(bandManager.getBandName(GSM850_PCS_MODE));
  Serial.print("6 ");
  Serial.println(bandManager.getBandName(GSM850_EGSM_DCS_PCS_MODE));

  // Empty the incoming buffer
  while(Serial.available())
    Serial.read();
  // Wait for an answer, just look at the first character
  while(!Serial.available());
  char c= Serial.read();
  
  // Now, according to input, select result
  // If the user has not selected something between 1-6
  // result in UNDEFINED

  switch(c)
  {
      case '1':
        result=EGSM_MODE;
        break;
      case '2':
        result=DCS_MODE;
        break;
      case '3':
        result=PCS_MODE;
        break;
      case '4':
        result=EGSM_DCS_MODE;
        break;
      case '5':
        result=GSM850_PCS_MODE;
        break;
      case '6':
        result=GSM850_EGSM_DCS_PCS_MODE;
        break;
      default:
        result=UNDEFINED;
  };
    
  return result;
}
