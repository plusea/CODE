/*
 Chat  Server
 
 A simple server that distributes any incoming messages to all
 connected clients.  To use telnet to  your device's IP address and type.
 You can see the client's input in the serial monitor as well.
 
 Circuit:
 * GSM shield attached
 
 created 18 Dec 2009
 by David A. Mellis
 modified 8 Mar 2012
 by Tom Igoe
 
 */



#include <GSM3.h>

GprsServer server(23);

boolean gotAMessage = false; // whether or not you got a message from the client yet

void setup() {
  // initialize serial:
  Serial.begin(9600);

  status = gsm.begin();
  if ( status != GSM_CONNECTED) { 
    Serial.println("Couldn't get a GSM connection");
    while(true);
  } 
  else {
    gsm.attachGPRS();
    Serial.println("Connected to GPRS network");
    server.begin();
    printGsmStatus();
  }
}
void loop() {
  // wait for a new client:
  GprsClient client = server.available();

  // when the client sends the first byte, say hello:
  if (client) {
    if (!gotAMessage) {
      Serial.println("We have a new client");
      client.println("Hello, client!"); 
      gotAMessage = true;
    }

    // read the bytes incoming from the client:
    char thisChar = client.read();
    // echo the bytes back to the client:
    server.write(thisChar);
    // echo the bytes to the server as well:
    Serial.print(thisChar);
  }
}


void printGsmStatus() {
  Serial.print("SIM card IMEI: ");
  Serial.println(gsm.imei());
  Serial.print("Band: ");
  Serial.println(gsm.getBand());

  Serial.print("Carrier: ");
  Serial.println(gsm.carrier());
  Serial.print("Signal Strength: ");
  Serial.print(gsm.getSignalStrength());
  Serial.println("dBm");
  Serial.print("Phone number: ");
  Serial.println(gsm.phoneNumber());

  // print your GSM shield's IP address:
  IPAddress ip = gsm.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}


