
/*
  Web client
 
 This sketch connects to a website (http://www.google.com)
 using a GSM shield.
 
 Circuit:
 * GSM shield attached
 
 created 8 Mar 2012
 by Tom Igoe
 */



#include <GSM3.h>

int status = GSM_IDLE_STATUS;
IPAddress server(74,125,115,105);  // Google

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
GprsClient client;

void setup() {
  Serial.begin(9600);
  
  status = gsm.begin();
  if ( status != GSM_CONNECTED) { 
    Serial.println("Couldn't get a GSM connection");
    while(true);
  } 
  else {
    gsm.attachGPRS();
    Serial.println("Connected to GPRS network");
    printGsmStatus();
    Serial.println("\nStarting connection to server...");
    // if you get a connection, report back via serial:
    if (client.connect(server, 80)) {
      Serial.println("connected to server");
      // Make a HTTP request:
      client.println("GET /search?q=arduino HTTP/1.0");
      client.println();
    }
  }
}

void loop() {
  // if there are incoming bytes available 
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();

    // do nothing forevermore:
    while(true);
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




