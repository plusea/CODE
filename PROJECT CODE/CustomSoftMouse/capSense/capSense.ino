

/*
 * Based on CapitiveSense Library Demo Sketch by Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */

#include <CapacitiveSensor.h>

// 10M resistor between pins 12 (=A9) & pin 20 (= A1), pin 20 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   capSensorPin = CapacitiveSensor(12,20);

void setup()                    
{
   //capSensorPin.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);
}

void loop()                    
{
    long start = millis();
    long total1 =  capSensorPin.capacitiveSensor(6);

    Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug windown spacing
    Serial.println(total1);                  // print sensor output 1
    delay(10);                             // arbitrary delay to limit data to serial port 
}

