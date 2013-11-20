/*
 
 This example helps you change your pin or remove it.
 
 Circuit:
 * GSM shield attached
 
 Created 12 Jun 2012
 by David del Peral
 */

// libraries
#include <GSM.h>

// pin manager object
GSMPin pinManager;

// save input in serial by user
String user_input = "";

// authenticated with PIN code
boolean auth = false;

// serial monitor result messages
String oktext = "OK";
String errortext = "ERROR";

void setup()
{
  // initialize serial communications
  Serial.begin(9600);
  
  Serial.println("Change PIN example\n");
  pinManager.begin();
  
  // check if the SIM have pin lock
  while(!auth){
    int pin_query = pinManager.isPIN();
    if(pin_query == 1)
    {
      // if SIM is locked, enter PIN code
      Serial.print("Enter PIN code: ");
      user_input = readSerial();
      // check PIN code
      if(pinManager.checkPIN(user_input) == 0)
      {
        auth = true;
        pinManager.setPinUsed(true);
        Serial.println(oktext);
      }
      else
      {  
        // if PIN code was incorrected
        Serial.println("Incorrect PIN. Remember that you have 3 opportunities.");
      }
    }
    else if(pin_query == -1)
    {
      // PIN code is locked, user must enter PUK code
      Serial.println("PIN locked. Enter PUK code: ");
      String puk = readSerial();
      Serial.print("Now, enter a new PIN code: ");
      user_input = readSerial();
      // check PUK code
      if(pinManager.checkPUK(puk, user_input) == 0)
      {
        auth = true;
        pinManager.setPinUsed(true);
        Serial.println(oktext);
      }
      else
      {
        // if PUK o the new PIN are incorrect
        Serial.println("Incorrect PUK or invalid new PIN. Try again!.");
      }
    }
    else if(pin_query == -2)
    {
      // the worst case, PIN and PUK are locked
      Serial.println("PIN & PUK locked. Use PIN2/PUK2 in a mobile phone.");
      while(true);
    }
    else
    {
      // SIM does not requires authetication 
      Serial.println("No pin necessary.");
      auth = true;
    }
  }
  
  // start GSM shield
  Serial.print("Checking register in GSM network...");
  if(pinManager.checkReg() == 0)
    Serial.println(oktext);
  // if you are connect by roaming
  else if(pinManager.checkReg() == 1)
    Serial.println("ROAMING " + oktext);  
  else
  {
    // error connection
    Serial.println(errortext);
    while(true);
  }
}

void loop()
{
  // Function loop implements pin management user menu
  // Only if you SIM use pin lock, you can change PIN code
  // user_op variables save user option
  
  Serial.println("Choose an option:\n1 - On/Off PIN.");
  if(pinManager.getPinUsed())
    Serial.println("2 - Change PIN.");
  String user_op = readSerial();
  if(user_op == "1")
  {
    Serial.println("Enter your PIN code:");
    user_input = readSerial();
    // activate/deactivate PIN lock
    pinManager.switchPIN(user_input);
  }
  else if(user_op == "2" & pinManager.getPinUsed())
  {
    Serial.println("Enter your actual PIN code:");
    String oldpin = readSerial();
    Serial.println("Now, enter your new PIN code:");
    String newpin = readSerial();
    // change PIN
    pinManager.changePIN(oldpin, newpin);
  }
  else
  {
    Serial.println("Incorrect option. Try again!.");
  }
  delay(1000);
}

/*
  Read input serial
 */
String readSerial()
{
  String text = "";
  while(1)
  {
    while (Serial.available() > 0)
    {
      char inChar = Serial.read();
      if (inChar == '\n')
      {
        return text;
      }
      if(inChar!='\r')
        text += inChar;
    }
  }
}
