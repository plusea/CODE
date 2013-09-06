/*
  Firmata.cpp - Firmata library
  Copyright (C) 2006-2008 Hans-Christoph Steiner.  All rights reserved.
 
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.
*/

//******************************************************************************
//* Includes
//******************************************************************************

#include "SSFirmata.h"
#include "HardwareSerial.h"

extern "C" {
#include <string.h>
#include <stdlib.h>
}

#define MAX(a,b) \
({ __typeof__ (a) _a = (a); \
__typeof__ (b) _b = (b); \
_a > _b ? _a : _b; })

#define MIN(a,b) \
({ __typeof__ (a) _a = (a); \
__typeof__ (b) _b = (b); \
_a < _b ? _a : _b; })

//******************************************************************************
//* Support Functions
//******************************************************************************

void SSFirmataClass::sendValueAsTwo7bitBytes(int value)
{
    bleSend(value & B01111111);
    bleSend(value >> 7 & B01111111);
}

void SSFirmataClass::startSysex(void)
{
  bleSend(START_SYSEX);
}

void SSFirmataClass::endSysex(void)
{
  bleSend(END_SYSEX);
}



//******************************************************************************
//* Constructors
//******************************************************************************

SSFirmataClass::SSFirmataClass(SoftwareSerial &s) : FirmataSerial(s)
{
  //Serial.println("initialized with serial: %d",(&FirmataSerial));
  sendBufferStart = 0;
  sendBufferCount = 0;
  memset(emptySendBuffer,END_SYSEX,BLE_BUFFER_SIZE);
    
  firmwareVersionCount = 0;
  systemReset();
}

//******************************************************************************
//* Public Methods
//******************************************************************************

/* begin method for overriding default serial bitrate */
void SSFirmataClass::begin(void)
{
  begin(19200);
}

/* begin method for overriding default serial bitrate */
void SSFirmataClass::begin(long speed)
{
    //Serial.begin(speed);
    FirmataSerial.begin(speed);

    //blinkVersion();
    //printVersion();
    printFirmwareVersion();
}

void SSFirmataClass::begin(SoftwareSerial &s)
{
  FirmataSerial = s;
  systemReset();
  printVersion();
  printFirmwareVersion();
}

void SSFirmataClass::bleSend(byte data){

    int oldSendBufferCount = sendBufferCount;
    
    if(sendBufferCount >= 0){
    int idx = (sendBufferStart + sendBufferCount) % SEND_BUFFER_SIZE;
    
    
    sendBuffer[idx] = data;
    sendBufferCount++;
    if(sendBufferCount > SEND_BUFFER_SIZE){
        sendBufferCount = SEND_BUFFER_SIZE;
        Serial.println("Warning, bleSendBuffer is full!");
        //Serial.println(sendBufferCount);
    }
    }
    
    if(sendBufferCount < 0){
        
        Serial.print("Error, sendBufferCount got corrupted! ");
        Serial.print(sendBufferCount);
        Serial.print(" old ");
        Serial.println(oldSendBufferCount);
        
    }
}

void SSFirmataClass::bleBufferReset(void){
    sendBufferCount = 0;
    sendBufferStart = 0;
}

void SSFirmataClass::bleFlush(void)
{
    if(sendBufferCount > 0){
                
        byte buf[BLE_BUFFER_SIZE];
        
        int numBytesSend = MIN(BLE_BUFFER_SIZE,sendBufferCount);
        
        totalBytesSent += numBytesSend;
        
        if(sendBufferStart + numBytesSend > SEND_BUFFER_SIZE){
            
            int firstPartSize = SEND_BUFFER_SIZE - sendBufferStart ;
            
            memcpy(buf,&sendBuffer[0] + sendBufferStart,firstPartSize);
            memcpy(&buf[0] + firstPartSize,&sendBuffer[0],numBytesSend-firstPartSize);
            
        } else {
            memcpy(&buf[0],&sendBuffer[0] + sendBufferStart,numBytesSend);
            
        }
        
        //fill buffer to BLE_BUFFER_SIZE so it notifies
        int missing = BLE_BUFFER_SIZE - numBytesSend;
        if(missing > 0) {
            memcpy(&buf[0]+numBytesSend,&emptySendBuffer[0],missing);
        }
        
        FirmataSerial.write(&buf[0],BLE_BUFFER_SIZE);
        
        /*
        for (int i = 0; i < BLE_BUFFER_SIZE; i++) {
            Serial.print(buf[i]);
            Serial.print(" ");
        }
        Serial.println("");*/
        
        sendBufferCount -= numBytesSend;
        sendBufferStart = (sendBufferStart + numBytesSend) % SEND_BUFFER_SIZE;
   }
}

void SSFirmataClass::blePrintSendBufferBetweenStartAndEnd(){
    //Serial.println("Printin SendBuf");
    
    for (int i = sendBufferStart; i < MIN(SEND_BUFFER_SIZE, sendBufferStart + sendBufferCount) ; i++) {
        if(i!= 0 && i%10==0){
            Serial.print("(");
            Serial.print(i);
            Serial.print(") ");
        }
        
        Serial.print((int) *(sendBuffer + i));
        if(i == sendBufferStart){
            Serial.print("*");
        } else if(i==sendBufferStart + sendBufferCount-1){
            Serial.print("**");
        }
        Serial.print(" ");
    }
    
    if(sendBufferStart + sendBufferCount >= SEND_BUFFER_SIZE){
        
        for (int i = 0; i < sendBufferCount - (SEND_BUFFER_SIZE - sendBufferStart); i++) {
            if(i!= 0 && i%10==0){
                Serial.print("(");
                Serial.print(i);
                Serial.print(") ");
            }
            
            Serial.print((int) *(sendBuffer + i));
            if(i == sendBufferStart){
                Serial.print("*");
            } else if(i==sendBufferStart + sendBufferCount-1){
                Serial.print("**");
            }
            Serial.print(" ");
        }
    }
    
    Serial.println();
}

// output the protocol version message to the serial port
void SSFirmataClass::printVersion(void) {
    
    Serial.println("Sending version: ");
    
    Serial.print(REPORT_VERSION);
    Serial.print(" ");
    Serial.print(FIRMATA_MAJOR_VERSION);
    Serial.print(" ");
    Serial.println(FIRMATA_MINOR_VERSION);
    
    bleSend(REPORT_VERSION);
    bleSend(FIRMATA_MAJOR_VERSION);
    bleSend(FIRMATA_MINOR_VERSION);
}

void SSFirmataClass::blinkVersion(void)
{    
  // flash the pin with the protocol version
  pinMode(VERSION_BLINK_PIN,OUTPUT);
  pin13strobe(FIRMATA_MAJOR_VERSION, 40, 210);
  delay(250);
  pin13strobe(FIRMATA_MINOR_VERSION, 40, 210);
  delay(125);
}

void SSFirmataClass::printFirmwareVersion(void) {
    byte i;
    
    
    if(firmwareVersionCount) { // make sure that the name has been set before reporting
        startSysex();
        
        bleSend(REPORT_FIRMWARE);
        bleSend(firmwareVersionVector[0]);
        bleSend(firmwareVersionVector[1]);
        
        for(i=2; i<firmwareVersionCount; ++i) {
            sendValueAsTwo7bitBytes(firmwareVersionVector[i]);
        }
        endSysex();
        
        Serial.print("sending firmware ");
        Serial.println(sendBufferCount);
    }
}

void SSFirmataClass::setFirmwareNameAndVersion(const char *name, byte major, byte minor)
{
  const char *filename;
  char *extension;

    Serial.println("setting firmware name and version");
    
  // parse out ".cpp" and "applet/" that comes from using __FILE__
  extension = strstr(name, ".cpp");
  filename = strrchr(name, '/') + 1; //points to slash, +1 gets to start of filename
  // add two bytes for version numbers
  if(extension && filename) {
    firmwareVersionCount = extension - filename + 2;
  } else {
    firmwareVersionCount = strlen(name) + 2;
    filename = name;
  }
  firmwareVersionVector = (byte *) malloc(firmwareVersionCount);
  firmwareVersionVector[firmwareVersionCount] = 0;
  firmwareVersionVector[0] = major;
  firmwareVersionVector[1] = minor;
  strncpy((char*)firmwareVersionVector + 2, filename, firmwareVersionCount - 2);
  // alas, no snprintf on Arduino
  //    snprintf(firmwareVersionVector, MAX_DATA_BYTES, "%c%c%s", 
  //             (char)major, (char)minor, firmwareVersionVector);
}

//------------------------------------------------------------------------------
// Serial Receive Handling

int SSFirmataClass::available(void)
{
  return FirmataSerial.available();
}

void SSFirmataClass::processSysexMessage(void)
{
  switch(storedInputData[0]) {
  case REPORT_FIRMWARE:
    printFirmwareVersion();
    break;
  case STRING_DATA:
    if(currentStringCallback) {
      byte bufferLength = (sysexBytesRead - 1) / 2;
      char *buffer = (char*)malloc(bufferLength * sizeof(char));
      byte i = 1;
      byte j = 0;
      while(j < bufferLength) {
        buffer[j] = (char)storedInputData[i];
        i++;
        buffer[j] += (char)(storedInputData[i] << 7);
        i++;
        j++;
      }
      (*currentStringCallback)(buffer);
    }
    break;
  default:
    if(currentSysexCallback)
      (*currentSysexCallback)(storedInputData[0], sysexBytesRead - 1, storedInputData + 1);
                               
  }
}

void SSFirmataClass::processInput(void)
{
    
  int inputData = FirmataSerial.read(); // this is 'int' to handle -1 when no data
  int command;
    /*
    Serial.print("reads ");
    Serial.println(inputData);*/
    
  // TODO make sure it handles -1 properly

  if (parsingSysex) {
    if(inputData == END_SYSEX) {
      //stop sysex byte      
      parsingSysex = false;
      //fire off handler function
      processSysexMessage();
    } else {
      //normal data byte - add to buffer
      storedInputData[sysexBytesRead] = inputData;
      sysexBytesRead++;
    }
  } else if( (waitForData > 0) && (inputData < 128) ) {
      if(waitForData >= MAX_DATA_BYTES){
          waitForData = 0;
      }
      
    waitForData--;
    storedInputData[waitForData] = inputData;
    if( (waitForData==0) && executeMultiByteCommand ) { // got the whole message
      switch(executeMultiByteCommand) {
      case ANALOG_MESSAGE:
        if(currentAnalogCallback) {
          (*currentAnalogCallback)(multiByteChannel,
                                   (storedInputData[0] << 7)
                                   + storedInputData[1]);
        }
        break;
      case DIGITAL_MESSAGE:
        if(currentDigitalCallback) {
          (*currentDigitalCallback)(multiByteChannel,
                                    (storedInputData[0] << 7)
                                    + storedInputData[1]);
        }
        break;
      case SET_PIN_MODE:
        if(currentPinModeCallback)
          (*currentPinModeCallback)(storedInputData[1], storedInputData[0]);
        break;
      case REPORT_ANALOG:
        if(currentReportAnalogCallback)
          (*currentReportAnalogCallback)(multiByteChannel,storedInputData[0]);
        break;
      case REPORT_DIGITAL:
        if(currentReportDigitalCallback)
          (*currentReportDigitalCallback)(multiByteChannel,storedInputData[0]);
        break;
      }
      executeMultiByteCommand = 0;
    }
  } else {
    // remove channel info from command byte if less than 0xF0
    if(inputData < 0xF0) {
      command = inputData & 0xF0;
      multiByteChannel = inputData & 0x0F;
    } else {
      command = inputData;
      // commands in the 0xF* range don't use channel data
    }
    switch (command) {
    case ANALOG_MESSAGE:
    case DIGITAL_MESSAGE:
    case SET_PIN_MODE:
      waitForData = 2; // two data bytes needed
      executeMultiByteCommand = command;
      break;
    case REPORT_ANALOG:
    case REPORT_DIGITAL:
      waitForData = 1; // two data bytes needed
      executeMultiByteCommand = command;
      break;
    case START_SYSEX:
      parsingSysex = true;
      sysexBytesRead = 0;
      break;
    case SYSTEM_RESET:
            Serial.println("going to reset!");
      systemReset();
      break;
    case REPORT_VERSION:
      printVersion();
      break;
    }
  }
    
    //Serial.println("after read");
    
}

//------------------------------------------------------------------------------
// Serial Send Handling

// send an analog message
void SSFirmataClass::sendAnalog(byte pin, int value) 
{
  // pin can only be 0-15, so chop higher bits
 
    bleSend(ANALOG_MESSAGE | (pin & 0xF));
    
  sendValueAsTwo7bitBytes(value);
}

// send a single digital pin in a digital message
void SSFirmataClass::sendDigital(byte pin, int value) 
{
  /* TODO add single pin digital messages to the protocol, this needs to
   * track the last digital data sent so that it can be sure to change just
   * one bit in the packet.  This is complicated by the fact that the
   * numbering of the pins will probably differ on Arduino, Wiring, and
   * other boards.  The DIGITAL_MESSAGE sends 14 bits at a time, but it is
   * probably easier to send 8 bit ports for any board with more than 14
   * digital pins.
   */

  // TODO: the digital message should not be sent on the serial port every
  // time sendDigital() is called.  Instead, it should add it to an int
  // which will be sent on a schedule.  If a pin changes more than once
  // before the digital message is sent on the serial port, it should send a
  // digital message for each change.

  //    if(value == 0)
  //        sendDigitalPortPair();
}


// send 14-bits in a single digital message (protocol v1)
// send an 8-bit port in a single digital message (protocol v2)
void SSFirmataClass::sendDigitalPort(byte portNumber, int portData)
{    
    bleSend(DIGITAL_MESSAGE | (portNumber & 0xF));
    bleSend((byte)portData % 128);
    bleSend(portData >> 7);
}


void SSFirmataClass::sendSysex(byte command, byte bytec, byte* bytev) 
{
  byte i;
  startSysex();
  bleSend(command);
  for(i=0; i<bytec; i++) {
    sendValueAsTwo7bitBytes(bytev[i]);
  }
  endSysex();
}

void SSFirmataClass::sendString(byte command, const char* string) 
{
  sendSysex(command, strlen(string), (byte *)string);
}


// send a string as the protocol string type
void SSFirmataClass::sendString(const char* string) 
{
  sendString(STRING_DATA, string);
}


// Internal Actions/////////////////////////////////////////////////////////////

// generic callbacks
void SSFirmataClass::attach(byte command, callbackFunction newFunction)
{
  switch(command) {
  case ANALOG_MESSAGE: currentAnalogCallback = newFunction; break;
  case DIGITAL_MESSAGE: currentDigitalCallback = newFunction; break;
  case REPORT_ANALOG: currentReportAnalogCallback = newFunction; break;
  case REPORT_DIGITAL: currentReportDigitalCallback = newFunction; break;
  case SET_PIN_MODE: currentPinModeCallback = newFunction; break;
  }
}

void SSFirmataClass::attach(byte command, systemResetCallbackFunction newFunction)
{
  switch(command) {
  case SYSTEM_RESET: currentSystemResetCallback = newFunction; break;
  }
}

void SSFirmataClass::attach(byte command, stringCallbackFunction newFunction)
{
  switch(command) {
  case STRING_DATA: currentStringCallback = newFunction; break;
  }
}

void SSFirmataClass::attach(byte command, sysexCallbackFunction newFunction)
{
  currentSysexCallback = newFunction;
}

void SSFirmataClass::detach(byte command)
{
  switch(command) {
  case SYSTEM_RESET: currentSystemResetCallback = NULL; break;
  case STRING_DATA: currentStringCallback = NULL; break;
  case START_SYSEX: currentSysexCallback = NULL; break;
  default:
    attach(command, (callbackFunction)NULL);
  }
}

// sysex callbacks
/*
 * this is too complicated for analogReceive, but maybe for Sysex?
 void EITFirmataClass::attachSysex(sysexFunction newFunction)
 {
 byte i;
 byte tmpCount = analogReceiveFunctionCount;
 analogReceiveFunction* tmpArray = analogReceiveFunctionArray;
 analogReceiveFunctionCount++;
 analogReceiveFunctionArray = (analogReceiveFunction*) calloc(analogReceiveFunctionCount, sizeof(analogReceiveFunction));
 for(i = 0; i < tmpCount; i++) {
 analogReceiveFunctionArray[i] = tmpArray[i];
 }
 analogReceiveFunctionArray[tmpCount] = newFunction;
 free(tmpArray);
 }
*/

//******************************************************************************
//* Private Methods
//******************************************************************************



// resets the system state upon a SYSTEM_RESET message from the host software
void SSFirmataClass::systemReset(void)
{
  byte i;

  waitForData = 0; // this flag says the next serial input will be data
  executeMultiByteCommand = 0; // execute this after getting multi-byte data
  multiByteChannel = 0; // channel data for multiByteCommands

  for(i=0; i<MAX_DATA_BYTES; i++) {
    storedInputData[i] = 0;
  }

  parsingSysex = false;
  sysexBytesRead = 0;

  if(currentSystemResetCallback)
    (*currentSystemResetCallback)();

  //flush(); //TODO uncomment when Firmata is a subclass of HardwareSerial
}



// =============================================================================
// used for flashing the pin for the version number
void SSFirmataClass::pin13strobe(int count, int onInterval, int offInterval) 
{
  byte i;
  pinMode(VERSION_BLINK_PIN, OUTPUT);
  for(i=0; i<count; i++) {
    delay(offInterval);
    digitalWrite(VERSION_BLINK_PIN, HIGH);
    delay(onInterval);
    digitalWrite(VERSION_BLINK_PIN, LOW);
  }
}

SoftwareSerial softwareSerial(2,3);
// make one instance for the user to use
SSFirmataClass SSFirmata(softwareSerial);

