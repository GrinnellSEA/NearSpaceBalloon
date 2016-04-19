/*
 * NEAR SPACE BALLOON PROJECT
 * FLIGHT COMPUTER CODE
 *
 * GRINNELL SPACE EXPLORATION AGENCY
 *
 * © 2015.  All Rights Reserved.
 */

#include <EEPROM.h>
#include "temp.h"
#include "pressure.h"

int loop_count = 0;

// runs once at start
void setup() {
    Serial.begin(9600); // begin logging

//    setupTemperatureSensor() || error("Temperature sensor setup failed.");
//    setupPressureSensor() || error("Pressure sensor setup failed.");
}

// runs continuously
void loop() {
//    double kelvin = getTemperature();
//    double farenheit = toFarenheit(kelvin);
//    byte temp_int = (int) map(farenheit, 0, 51, 0, 255);
    byte temp_int = 5;
    byte pres_int = 7;
//    double mb = getPressure(); // don't do anything with it.
//    byte pres_int = (int) map(mb, 950, 1050, 0, 255);

    long voltage = readVcc();
    byte vcc_int = (int) map(voltage, 2000, 7100, 0, 255);

    if (loop_count % 5 == 0) { // every five minutes
        // store temp
        EEPROM.write(0, temp_int);
        // and pressure
        EEPROM.write(1, pres_int);
        //and voltage
        EEPROM.write(2, vcc_int);
        // and iteration
        int iteration_count = loop_count / 5;
        EEPROM.write(3, iteration_count);
    }

    loop_count++;
    delay(60000); // every minute
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
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
    ADMUX = _BV(MUX5) | _BV(MUX0);
#elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    ADMUX = _BV(MUX3) | _BV(MUX2);
#else
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#endif  

    delay(2); // Wait for Vref to settle
    ADCSRA |= _BV(ADSC); // Start conversion
    while (bit_is_set(ADCSRA,ADSC)); // measuring

    uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH  
    uint8_t high = ADCH; // unlocks both

    long result = (high<<8) | low;

    result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
    return result; // Vcc in millivolts
}
