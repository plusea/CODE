/*
 Chat Server
 
 A simple server that distributes any incoming messages to all
 connected clients.  To use telnet to your device's IP address and type.
 You can see the client's input in the serial monitor as well.
 
 Circuit:
 * GSM shield attached
 
 created 18 Dec 2009
 by David A. Mellis
 modified 8 Mar 2012
 by Tom Igoe
 
 */

// libraries
#include <GSM.h>

// PIN Number
#define PINNUMBER ""

// APN data
#define GPRS_APN       "GPRS_APN" // replace your GPRS APN
#define GPRS_LOGIN     "login"    // replace with your GPRS login
#define GPRS_PASSWORD  "password" // replace with your GPRS password

// initialize the library instance
GSMClient client;
GPRS gprs;
GSM gsmAccess;     // include a 'true' parameter for debug enabled
GSMServer server(80);       // port 80 (http default)

// timeout
const unsigned long __TIMEOUT__ = 10*1000;

boolean gotAMessage = false; // whether or not you got a message from the client yet

uint8_t bufferRead [50]; // read buffer

void setup()
{
  // initialize serial communications
  Serial.begin(9600);
  
  // connection state
  boolean notConnected = true;
  
  // Start GSM shield
  // If your SIM has PIN, pass it as a parameter of begin() in quotes
  while(notConnected)
  {
    if((gsmAccess.begin(PINNUMBER)==GSM_READY) &
        (gprs.attachGPRS(GPRS_APN, GPRS_LOGIN, GPRS_PASSWORD)==GPRS_READY))
      notConnected = false;
    else
    {
      Serial.println("Not connected");
      delay(1000);
    }
  }
  
  Serial.println("Connected to GPRS network");
  
  // Start server
  server.begin();
  waitForResponseServer();
  
  // Get IP.
  IPAddress LocalIP = gprs.getIPAddress();
  if (!waitForResponseServer())
  {
      Serial.println("Couldn't get server IP address");
      while(true);
  } 
  else
  {
      Serial.println("Server IP address=");
      Serial.println(LocalIP);
  }
}

void loop() 
{
  // listen for incoming clients
  GSM3MobileClientService client = server.available();

  // when the client sends the first byte, say hello:
  if (client) 
  {
    while (client.connected()) 
    {
        // say hello 
        if (!gotAMessage) 
        {
          Serial.println("We have a new client");
          client.println("Hello, client!"); 
          gotAMessage = true;
        }
    
        client.read(bufferRead, 50);
        if (waitForResponseGsm()) 
        {
          client.write(bufferRead);
          Serial.print((const char *)bufferRead); // print client message
        }
        delay(100);
    }
    
  }
}

/*
  Wait for the GSM response
*/
bool waitForResponseGsm() 
{
  unsigned long m=millis();
  while(((millis()-m)< __TIMEOUT__ )&&(gsmAccess.ready()==0)) 
  {
    // wait for a response from the modem:
    delay(1000);
  } 
  if (gsmAccess.ready()==1) return true;
  else return false;
}

/*
  Wait for the network server response
*/
bool waitForResponseServer() 
{
  unsigned long m=millis();
  while(((millis()-m)< __TIMEOUT__ )&&(server.ready()==0)) 
  {
    // wait for a response from the modem:
    delay(1000);
  } 
  if (server.ready()==1) return true;
  else return false;
}

