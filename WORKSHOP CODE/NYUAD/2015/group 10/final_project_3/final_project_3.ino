

/*
This software was made to demonstrate how to quickly get your Atlas Scientific product running on the Arduino platform.
 An Arduino Duemilanove board was used to test this code.
 This code was written in the Arudino 1.0 IDE
 Modify the code to fit your system.
 Code efficacy was NOT considered, this is a demo only.
 The soft serial port TX line goes to the RX pin.
 The soft serial port RX line goes to the TX pin.
 Make sure you also connect to power and GND pins to power and a common ground.
 Data is received and re-sent through the Arduinos hardware UART TX line.
 Open TOOLS > serial monitor, set the serial monitor to the correct serial port and set the baud rate to 38400.
 Remember, select carriage return from the drop down menu next to the baud rate selection; not "both NL & CR".
 The data from the Atlas Scientific product will come out on the serial monitor.
 Type in a command in the serial monitor and the Atlas Scientific product will respond.
 */




#include <SoftwareSerial.h>                                                    //add the soft serial libray
#define rxpin 10                                                                //set the RX pin to pin 2
#define txpin 11                                                                //set the TX pin to pin 3
#define sensorRSTpin 8

int red;
int green;
int blue;

int redPin=3;
int greenPin=5;
int bluePin=6;


String color[3];
int i=0;

SoftwareSerial myserial(rxpin, txpin);                                         //enable the soft serial port


String inputstring = "";                                                       //a string to hold incoming data from the PC
String sensorstring = "";                                                      //a string to hold the data from the Atlas Scientific product
boolean input_stringcomplete = false;                                          //have we received all the data from the PC
boolean sensor_stringcomplete = false;                                         //have we received all the data from the Atlas Scientific product


void setup(){                                                                //set up the hardware
  pinMode(sensorRSTpin,OUTPUT);
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  Serial.begin(38400);                                                      //set baud rate for the hardware serial port to 38400
  myserial.begin(38400);                                                    //set baud rate for software serial port to 38400
  inputstring.reserve(5);                                                   //set aside some bytes for receiving data from the PC
  sensorstring.reserve(30);   //set aside some bytes for receiving data from Atlas Scientific product
  digitalWrite(sensorRSTpin, HIGH);
  digitalWrite(sensorRSTpin, LOW);
}



void serialEvent() {                                                         //if the hardware serial port receives a char
  char inchar = (char)Serial.read();                               //get the char we just received
  inputstring += inchar;                                           //add it to the inputString
  if(inchar == '\r') {
    input_stringcomplete = true;
  }                //if the incoming character is a <CR>, set the flag
}  


void loop(){                                                                   //here we go....
  //Serial.println ( analogRead ( A1));
  analogWrite(redPin,red);
  analogWrite(greenPin,green);
  analogWrite(bluePin,blue);

  if (input_stringcomplete){                                                   //if a string from the PC has been recived in its entierty 
    myserial.print(inputstring);                                             //send that string to the Atlas Scientific product
    inputstring = "";                                                        //clear the string:
    input_stringcomplete = false;                                            //reset the flage used to tell if we have recived a completed string from the PC
  }


  while (myserial.available()) {                                               //while a char is holding in the serial buffer
    char inchar = (char)myserial.read();                                  //get the new char

    sensorstring += inchar; 




    //add it to the sensorString
    if (inchar == '\r') {
      sensor_stringcomplete = true;
      i=0;


    }                   //if the incoming character is a <CR>, set the flag
    else{
      if (inchar != ',') {
        color[i] += inchar;
      }
      if (inchar == ',') {
        i++;
      }

    }

    //input[0]=myserial.parseInt();
  }


  if (sensor_stringcomplete){ 

    //if a string from the Atlas Scientific product has been received in its entirety

    red=color[0].toInt();
    green=color[1].toInt();
    blue=color[2].toInt();
    // MAPPING RGB values from actual range (black/white balance) to full range (255)
    red = map(red,50,255,0,255);
    red = constrain(red,0,255);
    green = map(green,50,200,0,255);
    green = constrain(green,0,255);
    blue = map(blue,50,200,0,255);
    blue = constrain(blue,0,255);

    analogWrite(redPin, red);
    analogWrite(greenPin, green);
    analogWrite(bluePin, blue);

    Serial.print(sensorstring);
    Serial.print(" ;  ");
    for(int t=0;t<3;t++) {
      Serial.print(color[t]);
      color[t]=""; 
      Serial.print(" : ");
    }

    Serial.println("");                                          //use the hardware serial port to send that data to the PC


    sensorstring = "";                                                      //clear the string:
    sensor_stringcomplete = false;                                          //reset the flag used to tell if we have received a completed string from the Atlas Scientific product
    //       myserial.print("R\r");
  }
}







