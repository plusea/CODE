/*
    Receive.cpp
    Author: Seb Madgwick
*/

//------------------------------------------------------------------------------
// Includes

#include <Arduino.h>
#include "I2CBus.h"
#include "Receive.h"

//------------------------------------------------------------------------------
// Definitions

#define LED_PACKET_LENGTH   5
#define VIB_PACKET_LEGNTH   3
#define MISC_PACKET_LEGNTH  10
#define MAX_PACKET_LENGTH   10

//------------------------------------------------------------------------------
// Variables

char Receive::rxBuf[256];
unsigned char Receive::rxBufIndex;

//------------------------------------------------------------------------------
// Methods

void Receive::doTasks() {
    while(Serial.available() > 0) {
        static bool inSync = false;
        static int byteCount = 0;

        // Add new byte to buffer
        rxBuf[rxBufIndex++] = Serial.read();

        // Check if out of sync
        if (++byteCount > MAX_PACKET_LENGTH) {
            byteCount = MAX_PACKET_LENGTH;  // prevent overflow
            inSync = false;
        }

        // Decode LED packet
        if (rxBufIndex >= LED_PACKET_LENGTH) {
            if ((inSync ? rxBuf[0] : rxBuf[rxBufIndex - LED_PACKET_LENGTH]) == 'L') {
                if (calcChecksum(LED_PACKET_LENGTH) == 0) {
                    unsigned char red   = (unsigned char)rxBuf[rxBufIndex - (LED_PACKET_LENGTH - 1)];
                    unsigned char green = (unsigned char)rxBuf[rxBufIndex - (LED_PACKET_LENGTH - 2)];
                    unsigned char blue  = (unsigned char)rxBuf[rxBufIndex - (LED_PACKET_LENGTH - 3)];
                    I2CBus::setRGB(red, green, blue);
                    rxBufIndex = 0;
                    byteCount = 0;
                    inSync = true;
                }
            }
        }

        // Decode vibration motor packet
        if (rxBufIndex >= VIB_PACKET_LEGNTH) {
            if ((inSync ? rxBuf[0] : rxBuf[rxBufIndex - VIB_PACKET_LEGNTH]) == 'V') {
                if (calcChecksum(VIB_PACKET_LEGNTH) == 0) {
                    char value = (unsigned char)rxBuf[rxBufIndex - (VIB_PACKET_LEGNTH - 1)];
                    // TODO: process data
                    rxBufIndex = 0;
                    byteCount = 0;
                    inSync = true;
                }
            }
        }

        // Decode misc packet
        if (rxBufIndex >= MISC_PACKET_LEGNTH) {
            if ((inSync ? rxBuf[0] : rxBuf[rxBufIndex - MISC_PACKET_LEGNTH]) == 'M') {
                if (calcChecksum(MISC_PACKET_LEGNTH) == 0) {
                    char charArray[8];
                    charArray[0] = (unsigned char)rxBuf[rxBufIndex - (MISC_PACKET_LEGNTH - 1)];
                    charArray[1] = (unsigned char)rxBuf[rxBufIndex - (MISC_PACKET_LEGNTH - 2)];
                    charArray[2] = (unsigned char)rxBuf[rxBufIndex - (MISC_PACKET_LEGNTH - 3)];
                    charArray[3] = (unsigned char)rxBuf[rxBufIndex - (MISC_PACKET_LEGNTH - 4)];
                    charArray[4] = (unsigned char)rxBuf[rxBufIndex - (MISC_PACKET_LEGNTH - 5)];
                    charArray[5] = (unsigned char)rxBuf[rxBufIndex - (MISC_PACKET_LEGNTH - 6)];
                    charArray[6] = (unsigned char)rxBuf[rxBufIndex - (MISC_PACKET_LEGNTH - 7)];
                    charArray[7] = (unsigned char)rxBuf[rxBufIndex - (MISC_PACKET_LEGNTH - 8)];
                    // TODO: process data
                    rxBufIndex = 0;
                    byteCount = 0;
                    inSync = true;
                }
            }
        }
    }
}

char Receive::calcChecksum(const int packetLength) {
    unsigned char tempRxBufIndex = rxBufIndex - packetLength;
    unsigned char checksum = 0;
     while(tempRxBufIndex != rxBufIndex) {
        checksum ^= rxBuf[tempRxBufIndex++];
    }
    return checksum;
}

//------------------------------------------------------------------------------
// End of file
