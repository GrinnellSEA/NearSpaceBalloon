/*
 * NEAR SPACE BALLOON PROJECT
 * TEST AND LOGGING CODE
 *
 * GRINNELL SPACE EXPLORATION AGENCY
 *
 * © 2016.  All Rights Reserved.
 */

#include <EEPROM.h>
#include "temp.h"
#include "pressure.h"

#define INTERVAL (1*10*1000)
#define BLINK (500)

int address = 0;
int max_addr;

// runs once at start
void setup() {
    Serial.begin(9600); // begin logging

    max_addr = EEPROM.length();
    // clear memory
    for (int a = 0; a < max_addr; a++)
        EEPROM.update(a, 0);

    // setup LED_BUILTIN blink
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    setupTemperatureSensor() || error("Temperature sensor setup failed.");
    setupPressureSensor() || error("Pressure sensor setup failed.");
}

// runs continuously
void loop() {
    double kelvin = getTemperature();
    double farenheit = toFarenheit(kelvin);
    byte temp_int = memCompress(farenheit, 0, 102);

    double mb = getPressure(); // don't do anything with it.
    byte pres_int = memCompress(mb, 950, 1050);

    long voltage = readVcc();
    byte vcc_int = memCompress(voltage, 2000, 7100);

    // store data
    EEPROM.update(address + 0, temp_int);
    EEPROM.update(address + 1, pres_int);
    EEPROM.update(address + 2, vcc_int);
    address += 3;
    if (address + 3 >= max_addr) // If we'd run out of space next time
       address = 0; 

    digitalWrite(LED_BUILTIN, HIGH);
    delay(BLINK); 
    digitalWrite(LED_BUILTIN, LOW);
    delay(INTERVAL - BLINK); 
}

void end() { while (true) delay(1000); }

bool error(char *msg) {
    Serial.print("Error: ");
    Serial.println(msg);

    end();
    return false;
}

long readVcc() {
    // Read 1.1V reference against AVcc
    // set the reference to Vcc and the measurement to the internal 1.1V reference
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);

    delay(2); // Wait for Vref to settle
    ADCSRA |= _BV(ADSC); // Start conversion
    while (bit_is_set(ADCSRA,ADSC)); // measuring

    uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH  
    uint8_t high = ADCH; // unlocks both

    long result = (high<<8) | low;

    result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
    return result; // Vcc in millivolts
}

byte memCompress(double value, double in_min, double in_max) {
    return (byte) ((value - in_min) * 255 / (in_max - in_min));
}
