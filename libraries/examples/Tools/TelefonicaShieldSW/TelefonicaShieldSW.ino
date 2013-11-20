// libraries
#include <GSM3MobileClientService.h>
#include <GSM3ShieldV1AccessProvider.h>
#include <GSM3ShieldV1DataNetworkProvider.h>
#include <GSM3ShieldV1ClientProvider.h>
#include <GSM3ShieldV1DirectModemProvider.h>

// KEY (copy & paste from shield data page at BlueVia Arduino Shield website: arduinoshield.tid.es)
#define KEY "eb70f352b1"

// APN data
#define GPRS_APN       "bluevia.movistar.es" // replace your GPRS APN
#define GPRS_LOGIN     ""    // replace with your GPRS login
#define GPRS_PASSWORD  "" // replace with your GPRS password

// initialize the library instance
GSM3MobileClientService client(true);
GSM3ShieldV1ClientProvider s1client;
GSM3ShieldV1DataNetworkProvider gprs;
GSM3ShieldV1AccessProvider gsmAccess; // include a 'true' parameter for debug enabled
GSM3ShieldV1DirectModemProvider modemProvider;

// Telefonica's Shield backend server data
const char hostname[] = "arduinoshield.tid.es";
const char path[] = "/Arduino/receive.php";
const int kNetworkTimeout = 30*1000;
const int kNetworkDelay = 1000;

// transmission variables
uint8_t charReceived = 0;
unsigned long m;
unsigned long delayLong;

// buffers and I/O variables
#define numAuxCharacteres 39
char ICCID[35];
char bufAux[2] = "";
int countAux;
uint8_t LedR, LedG, LedB; //1 input, 0 output
uint8_t DigitalLSB = 112;
uint8_t DigitalMSB = 4/*63*/;
int countInputs = 4;

// serial monitor variables
uint8_t value;
char errortext[] = "ERROR";
String pwmtext = "\tPWM\t";
String intext = "\tIN\t";
String outext = "\tOUT\t";
String onetext = "1";
String zerotext = "0";
String D4 = "D4";
String D5 = "D5";
String D6 = "D6";
String D8 = "D8";
String D9 = "D9";
String D10 = "D10";
String D11 = "D11";
String D12 = "D12";
String D13 = "D13";

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
    if((gsmAccess.begin()==GSM_READY) &
        (gprs.attachGPRS(GPRS_APN, GPRS_LOGIN, GPRS_PASSWORD)==GPRS_READY))
      notConnected = false;
    else
    {
      Serial.println(errortext);
      delay(1000);
    }
  }

  Serial.println("Sending...");
}

void loop()
{
  // get M2M SIM iccid
  getICCID();
  
  uint8_t numberBytesICCID = strlen(ICCID);
  uint8_t numberKeyField = strlen(KEY) + 6;
  uint8_t numberBytes = numberBytesICCID + numberKeyField + numAuxCharacteres + countInputs;

  // error variable
  int err = 0;
  
  // connect to backend service
  if(client.connect(hostname, 80))
  {
    // make a POST petition with data
    client.print("POST ");
    client.print(path);
    client.println(" HTTP/1.0");

    // POST request required headers
    client.println("Host: arduinoshield.tid.es");
    client.println("Content-Type: application/x-www-form-urlencoded");  
    client.print("Content-Length: ");
    client.println(numberBytes);
    client.println();
        
    // send ICCID
    client.print(ICCID);
    client.print(",#KEY,");
    client.print(KEY);
    
    // send analog inputs
    client.print(",#A,");
    char bufAux[5]; 
    itoa (analogRead(A0), bufAux, 10);
    client.print(bufAux);
    client.print(",");
    itoa (analogRead(A1), bufAux, 10);
    client.print(bufAux);
    client.print(",");
    itoa (analogRead(A2), bufAux, 10);
    client.print(bufAux);
    client.print(",");
    itoa (analogRead(A3), bufAux, 10);
    client.print(bufAux);
    client.print(",");
    itoa (analogRead(A4), bufAux, 10);
    client.print(bufAux);
    client.print(",");
    itoa (analogRead(A5), bufAux, 10);
    client.print(bufAux);

    /*Serial.println();
    Serial.println(DigitalLSB);
    Serial.println(DigitalMSB);*/
    
    // send digital inputs
    client.print(",#D");
    // LSB
    for (int pin=4;pin<7;pin++) {
      if (DigitalLSB&(1<<pin)){
        client.print(",");
        client.print((uint8_t)digitalRead(pin)); 
      }
      else client.print(",");
    }
    // MSB
    for (int pin=0;pin<6;pin++) {
      if (DigitalMSB&(1<<pin)){
        client.print(",");
        client.print((uint8_t)digitalRead(pin+8)); 
      }
      else client.print(",");
    }
    
    // response from backend service
        
    unsigned long timeoutStart = millis();
    char c;
    int contAux=0;
    countInputs = 0;
        
    Serial.println("Pin\tMode\tValue");
        
    while((client.connected() || client.available()) && 
          ((millis() - timeoutStart) < kNetworkTimeout))
    {   
      if(client.available())
      {      
        if(c=client.read())
        {      
          
          //If KEY is incorrect
          if(c=='!')
          {
            Serial.println("KEY INCORRECT");
            while(true);
          }
          
          //Each direction of pins 4,5,6,8,9,10,11,12,13
          //1=input, 0=output, 2=PWM
          //And each value, only if output or PWM
          //LSB directions.
          //Pin 4
          if (contAux==1) {
            if (c=='1'){
              DigitalLSB |= 1<<4;
              countInputs++;
              pinMode(4, INPUT);
              Serial.println(D4 + intext);
            }
            else 
            {
              DigitalLSB &= ~(1<<4);
              pinMode(4, OUTPUT);
              if (c=='2'){
                value = client.read();
                analogWrite(4, value);
                Serial.println(D4 + pwmtext + value);
              }else if((client.read())=='1'){
                digitalWrite(4, HIGH);
                Serial.println(D4 + outext + onetext);
              }else{
                digitalWrite(4, LOW);
                Serial.println(D4 + outext + zerotext);
              }
            }
          }
          //Pin 5
          if (contAux==2) {
            if (c=='1') {
              DigitalLSB |= 1<<5;
              countInputs++;
              pinMode(5, INPUT);
            }
            else 
            {
              DigitalLSB &= ~(1<<5);
              pinMode(5, OUTPUT);
              if (c=='2'){
                value = client.read();
                analogWrite(5, value);
                Serial.println(D5 + pwmtext + value);
              }else if((client.read())=='1'){
                digitalWrite(5, HIGH);
                Serial.println(D5 + outext + onetext);
              }else{
                digitalWrite(5, LOW);
                Serial.println(D5 + outext + zerotext);
              }
            }
          }
          //Pin 6
          if (contAux==3) {
            if (c=='1') {
              DigitalLSB |= 1<<6;
              countInputs++;
              pinMode(6, INPUT);
            }
            else 
            {
              DigitalLSB &= ~(1<<6);
              pinMode(6, OUTPUT);
              if (c=='2'){
                value = client.read();
                analogWrite(6, value);
                Serial.println(D6 + pwmtext + value);
              }else if((client.read())=='1'){
                digitalWrite(6, HIGH);
                Serial.println(D6 + outext + onetext);
              }else{
                digitalWrite(6, LOW);
                Serial.println(D6 + outext + zerotext);
              }
            }
          }
          //MSB directions.
          //Pin 8, no PWM
          if (contAux==4) {
            if (c=='1') {
              DigitalMSB |= 1;
              countInputs++;
              pinMode(8, INPUT);
            }
            else
            {
              DigitalMSB &= ~(1);
              pinMode(8, OUTPUT);
              if((client.read())=='1'){
                digitalWrite(8, HIGH);
                Serial.println(D8 + outext + onetext);
              }else{
                digitalWrite(8, LOW);
                Serial.println(D8 + outext + zerotext);
              }
            }
          }
          //Pin 9
          if (contAux==5) {
            if (c=='1') {
              DigitalMSB |= 1<<1;
              countInputs++;
              pinMode(9, INPUT);
            }
            else 
            {
              DigitalMSB &= ~(1<<1);
              pinMode(9, OUTPUT);
              if (c=='2'){
                value = client.read();
                analogWrite(9, value);
                Serial.println(D9 + pwmtext + value);
              }else if((client.read())=='1'){
                digitalWrite(9, HIGH);
                Serial.println(D9 + outext + onetext);
              }else{
                digitalWrite(9, LOW);
                Serial.println(D9 + outext + zerotext);
              }
            }
          }
          //Pin 10
          if (contAux==6) {
            if (c=='1') {
              DigitalMSB |= 1<<2;
              countInputs++;
              pinMode(10, INPUT);
            }
            else 
            {
              DigitalMSB &= ~(1<<2);
              pinMode(10, OUTPUT);
              if (c=='2'){
                value = client.read();
                analogWrite(10, value);
                Serial.println(D10 + pwmtext + value);
              }else if((client.read())=='1'){
                digitalWrite(10, HIGH);
                Serial.println(D10 + outext + onetext);
              }else{
                digitalWrite(10, LOW);
                Serial.println(D10 + outext + zerotext);
              }
            }
          }
          //Pin 11
          if (contAux==7) {
            if (c=='1') {
              DigitalMSB |= 1<<3;
              countInputs++;
              pinMode(11, INPUT);
            }
            else 
            {
              DigitalMSB &= ~(1<<3);
              pinMode(11, OUTPUT);
              if (c=='2'){
                value = client.read();
                analogWrite(11, value);
                Serial.println(D11 + pwmtext + value);
              }else if((client.read())=='1'){
                digitalWrite(11, HIGH);
                Serial.println(D11 + outext + onetext);
              }else{
                digitalWrite(11, LOW);
                Serial.println(D11 + outext + zerotext);
              }
            }
          }
          //Pin 12, no PWM
          if (contAux==8) {
            if (c=='1') {
              DigitalMSB |= 1<<4;
              countInputs++;
              pinMode(12, INPUT);
            }
            else
            {
              DigitalMSB &= ~(1<<4);
              pinMode(12, OUTPUT);
              if((client.read())=='1'){
                digitalWrite(12, HIGH);
                Serial.println(D12 + outext + onetext);
              }else{
                digitalWrite(12, LOW);
                Serial.println(D12 + outext + zerotext);
              }
            }
          }
          //Pin 13, no PWM
          if (contAux==9) {
            if (c=='1') {
              DigitalMSB |= 1<<5;
              countInputs++;
              pinMode(13, INPUT);
            }
            else
            {
              DigitalMSB &= ~(1<<5);
              pinMode(13, OUTPUT);
              if((client.read())=='1'){
                digitalWrite(13, HIGH);
                Serial.println(D13 + outext + onetext);
              }else{
                digitalWrite(13, LOW);
                Serial.println(D13 + outext + zerotext);
              }
            }
          }
          //2 bytes for delay(seconds)
          if (contAux==10) {
            //Serial.println("\n");
            //Serial.println(byte(c));
            byte aux=(byte)(c);
            if (aux < 97) aux=aux-48;
            else aux=aux-87;
            delayLong = aux*1024;
            //Serial.println(delayLong);
            c=client.read();
            //Serial.println(byte(c));
            aux=(byte)(c);
            if (aux < 97) aux=aux-48;
            else aux=aux-87;
            delayLong += aux*256;
            //Serial.println(delayLong);
            c=client.read();
            //Serial.println(byte(c));
            aux=(byte)(c);
            if (aux < 97) aux=aux-48;
            else aux=aux-87;
            delayLong += aux*16;
            //Serial.println(delayLong);
            c=client.read();
            //Serial.println(byte(c));
            aux=(byte)(c);
            if (aux < 97) aux=aux-48;
            else aux=aux-87;
            delayLong += aux;
            //Serial.println(delayLong);
          }
          if ((c=='#')||(contAux > 0)) contAux++;
          //Serial.print(c);
        }
      }else{      
        delay(kNetworkDelay);     
      }
    }
  }else{
    Serial.print(errortext);
  }
  
  client.stop();
  
  Serial.print("Update: ");
  Serial.println(delayLong);
  delay(delayLong*1000);
}

void getICCID()
{
  strcpy(ICCID,"cadena=#ICCID,");
  String id_code = modemProvider.writeModemCommand("AT+QCCID", 2000);
  id_code.trim();
  id_code.replace("\n","");
  id_code.replace("\r","");
  char id_code_char[id_code.length()-2];
  id_code.toCharArray(id_code_char, id_code.length()-2);
  strcat(ICCID,(const char *)id_code_char);
  //Serial.println(ICCID);
}
