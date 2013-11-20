/*
 
 This example  prints out the IMEI number of the SIM card,
 then check to see if it's connected to a carrier. If so, 
 it prints the phone number associated with the card.
 Then it scans for nearby networks and prints out their signal strengths.
 
 
 Created 8 Mar 2012
 by Tom Igoe
 */

#include <GSM3.h>

void setup() {
  // initialize serial:
  Serial.begin(9600);
  Serial.println("Initializing GSM...");
  // print the IMEI of the SIM card whether connected or not:
  Serial.print("SIM card IMEI: ");
  Serial.println(gsm.imei());
  Serial.print("Subscriber IMSI: ");
  Serial.println(gsm.imsi());
  Serial.print("Band: ");
  Serial.println(gsm.getBand());

  // begin should try to connect to carrier:
  if (gsm.begin() == CONNECTED) {
    Serial.print("Carrier: ");
    Serial.println(gsm.carrier());
    Serial.print("Signal Strength: ");
    Serial.print(gsm.getSignalStrength(gsm.carrier()));
    Serial.print("Phone number: ");
    Serial.println(gsm.phoneNumber());
  } 

  // scan for existing networks:
  Serial.println("Scanning available networks...");
  listNetworks();
}

void loop() {
  delay(10000);
  // scan for existing networks:
  Serial.println("Scanning available networks...");
  listNetworks();
}

void listNetworks() {
  // scan for nearby networks:
  Serial.println("** Scan Networks **");
  byte numNetworks = gsm.scanNetworks();

  // print the list of networks seen:
  Serial.print("Network List:");
  Serial.println(numNetworks);

  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet<numNetworks; thisNet++) {
    Serial.print(thisNet);
    Serial.print("Network: ");
    Serial.print(gsm.carrier(thisNet));
    Serial.print("\t");
    Serial.print(gsm.getSignalStrength(gsm.carrier(thisNet)));
  }
}
