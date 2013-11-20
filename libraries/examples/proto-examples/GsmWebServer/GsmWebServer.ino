/*
  Web  Server
 
 A simple web server that shows the value of the analog input pins.
 using a GSM shield.

 Circuit:
 * GSM shield attached
 * Analog inputs attached to pins A0 through A5 (optional)
 
 created 8 Mar 2012
 by Tom Igoe
 */



#include <GSM3.h>

int status = GSM_IDLE_STATUS;

GprsServer server(80);

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
  // listen for incoming clients
  GprsClient client = server.available();
  if (client) {
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<html>");
          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(analogRead(analogChannel));
            client.println("<br />");       
          }
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
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


