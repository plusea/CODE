//==============================================================================
// Send.cpp
//==============================================================================
/*
    <description, licence, etc.>

    Assumes that Serial.begin has already been called.

    Packets include LRC checksum as last byte:
    http://en.wikipedia.org/wiki/Longitudinal_redundancy_check

    Date            Author            Notes
    dd/mm/yyyy        Seb Madgwick    Initial release
*/
//==============================================================================

//------------------------------------------------------------------------------
// Includes

#include "AHRS.h"
#include <Arduino.h>
#include "Calibration.h"
#include "FlexSensors.h"
#include "Send.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern AHRS ahrs;

//------------------------------------------------------------------------------
// Definitions

#define BINARY_PACKETS

typedef union {
    int intVal;
    struct {
        char lsb;
        char msb;
    };
} IntUnion;

//------------------------------------------------------------------------------
// Methods

void Send::flexSensorData() {
    char packet[64];
    int packetLength = 0;
    IntUnion intUnion;
    FlexSensors::read();    // read sensors before sending
#ifdef BINARY_PACKETS
    packet[packetLength++] = 'F';
    intUnion.intVal= (int)FlexSensors::channel[0];
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= (int)FlexSensors::channel[1];
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= (int)FlexSensors::channel[2];
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= (int)FlexSensors::channel[3];
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= (int)FlexSensors::channel[4];
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= (int)FlexSensors::channel[5];
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    packet[packetLength++] = calcChecksum(packet, packetLength);
#else
    packet[packetLength++] = 'F';
    packet[packetLength++] = ',';
    IntValToChars(packet, &packetLength, (int)FlexSensors::channel[0]);
    packet[packetLength++] = ',';
    IntValToChars(packet, &packetLength, (int)FlexSensors::channel[1]);
    packet[packetLength++] = ',';
    IntValToChars(packet, &packetLength, (int)FlexSensors::channel[2]);
    packet[packetLength++] = ',';
    IntValToChars(packet, &packetLength, (int)FlexSensors::channel[3]);
    packet[packetLength++] = ',';
    IntValToChars(packet, &packetLength, (int)FlexSensors::channel[4]);
    packet[packetLength++] = ',';
    IntValToChars(packet, &packetLength, (int)FlexSensors::channel[5]);
    packet[packetLength++] = ',';
    IntValToChars(packet, &packetLength, calcChecksum(packet, packetLength));
    packet[packetLength++] = '\r';
#endif
    Serial.write((uint8_t*)packet, packetLength);
}

void Send::sensorData() {
    char packet[128];
    int packetLength = 0;
    IntUnion intUnion;
    Serial.write((uint8_t*)packet, packetLength);
#ifdef BINARY_PACKETS
    packet[packetLength++] = 'S';
    intUnion.intVal= Calibration::gyrX;
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= Calibration::gyrY;
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= Calibration::gyrZ;
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= Calibration::accX;
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= Calibration::accY;
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= Calibration::accZ;
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= Calibration::magX;
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= Calibration::magY;
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= Calibration::magZ;
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    packet[packetLength++] = calcChecksum(packet, packetLength);
#else
    packet[packetLength++] = 'S';
    packet[packetLength++] = ',';
    IntValToChars(packet, &packetLength, Calibration::gyrX);
    packet[packetLength++] = ',';
    IntValToChars(packet, &packetLength, Calibration::gyrY);
    packet[packetLength++] = ',';
    IntValToChars(packet, &packetLength, Calibration::gyrZ);
    packet[packetLength++] = ',';
    IntValToChars(packet, &packetLength, Calibration::accX);
    packet[packetLength++] = ',';
    IntValToChars(packet, &packetLength, Calibration::accY);
    packet[packetLength++] = ',';
    IntValToChars(packet, &packetLength, Calibration::accZ);
    packet[packetLength++] = ',';
    IntValToChars(packet, &packetLength, Calibration::magX);
    packet[packetLength++] = ',';
    IntValToChars(packet, &packetLength, Calibration::magY);
    packet[packetLength++] = ',';
    IntValToChars(packet, &packetLength, Calibration::magZ);
    packet[packetLength++] = ',';
    IntValToChars(packet, &packetLength, calcChecksum(packet, packetLength));
    packet[packetLength++] = '\r';
#endif
    Serial.write((uint8_t*)packet, packetLength);
}

void Send::quaternionData() {
    char packet[64];
    int packetLength = 0;
#ifdef BINARY_PACKETS
    IntUnion intUnion;
    packet[packetLength++] = 'Q';
    intUnion.intVal= (int)(10000.0f * ahrs.q0);
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= (int)(-10000.0f * ahrs.q1);    // negated complex elements for quaternion conjugate
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= (int)(-10000.0f * ahrs.q2);
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= (int)(-10000.0f * ahrs.q3);
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    packet[packetLength++] = calcChecksum(packet, packetLength);
    packet[packetLength++] = intUnion.lsb;
#else
    packet[packetLength++] = 'Q';
    packet[packetLength++] = ',';
    IntValToChars(packet, &packetLength, (int)(10000.0f * ahrs.q0));
    packet[packetLength++] = ',';
    IntValToChars(packet, &packetLength, (int)(10000.0f * ahrs.q1));
    packet[packetLength++] = ',';
    IntValToChars(packet, &packetLength, (int)(10000.0f * ahrs.q2));
    packet[packetLength++] = ',';
    IntValToChars(packet, &packetLength, (int)(10000.0f * ahrs.q3));
    packet[packetLength++] = ',';
    IntValToChars(packet, &packetLength, calcChecksum(packet, packetLength));
    packet[packetLength++] = '\r';
#endif
    Serial.write((uint8_t*)packet, packetLength);
}

void Send::miscData(const char* const charArray) {
    char packet[64];
    int packetLength = 0;
    IntUnion intUnion;
    packet[packetLength++] = 'M';
    for(int i = 0; i < 8; i++) {
        packet[packetLength++] = charArray[i];
    }
    packet[packetLength++] = calcChecksum(packet, packetLength);
    Serial.write((uint8_t*)packet, packetLength);
}

void Send::IntValToChars(char* const charArray, int* const index, int i) {
    static const char asciiDigits[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', };
    div_t n;
    int print = 0;
    if(i < 0) {
        charArray[(*index)++] = '-';
        i = -i;
    }
    if(i >= 10000) {
        n = div(i, 10000);
        charArray[(*index)++] = asciiDigits[n.quot];
        i = n.rem;
        print = 1;
    }
    if(i >= 1000 || print) {
        n = div(i, 1000);
        charArray[(*index)++] = asciiDigits[n.quot];
        i = n.rem;
        print = 1;
    }
    if(i >= 100 || print) {
        n = div(i, 100);
        charArray[(*index)++] = asciiDigits[n.quot];
        i = n.rem;
        print = 1;
    }
    if(i >= 10 || print) {
        n = div(i, 10);
        charArray[(*index)++] = asciiDigits[n.quot];
        i = n.rem;
    }
    charArray[(*index)++] = asciiDigits[i];
}

char Send::calcChecksum(const char* const packet, const int packetLength) {
    int i = 0;
    char checksum = 0;
    while(i < packetLength) {
        checksum ^= packet[i++];
    }
    return checksum;
}

//------------------------------------------------------------------------------
// End of file
