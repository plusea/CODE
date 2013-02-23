typedef union {
    int intVal;
    struct {
        char lsb;
        char msb;
    };
} IntUnion;

int channel[6];

void setup() {
    Serial.begin(115200);
}

void loop() {
    channel[0] = 12345;    // repeat for [1,2,3,4,5]
    SendFlexSensorData();
    delay(10);
}

void SendFlexSensorData() {
    char packet[64];
    int packetLength = 0;
    IntUnion intUnion;
    FlexSensors::read();    // read sensors before sending
    packet[packetLength++] = 'F';
    intUnion.intVal= channel[0];
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= channel[1];
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= channel[2];
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= channel[3];
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= channel[4];
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= channel[5];
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    packet[packetLength++] = calcChecksum(packet, packetLength);
    Serial.write((uint8_t*)packet, packetLength);
}

char calcChecksum(const char* const packet, const int packetLength) {
    int i = 0;
    char checksum = 0;
    while(i < packetLength) {
        checksum ^= packet[i++];
    }
    return checksum;
}
