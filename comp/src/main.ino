/*
 * NEAR SPACE BALLOON PROJECT
 * FLIGHT COMPUTER CODE
 *
 * GRINNELL SPACE EXPLORATION AGENCY
 *
 * (c) 2015.  All Rights Reserved.
 */

#include "temp.h"

// runs once at start
void setup() {
    Serial.begin(9600); // begin logging

    setupTemperatureSensor();
}

// runs continuously
void loop() {
    for (int i = 0; i < 15; i++) { // print temp every second for 15 seconds, then end
        double kelvin = getTemperature();
        double farenheit = toFarenheit(kelvin);
        Serial.println(farenheit);
        delay(1000);
    }

    end();
}

void end() { while (true) delay(1000); }
