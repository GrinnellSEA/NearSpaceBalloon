/*
 * NEAR SPACE BALLOON PROJECT
 * FLIGHT COMPUTER CODE
 *
 * GRINNELL SPACE EXPLORATION AGENCY
 *
 * (c) 2015.  All Rights Reserved.
 */

#include "temp.h"
#include "pressure.h"

// runs once at start
void setup() {
    Serial.begin(9600); // begin logging

    setupTemperatureSensor() || error("Temperature sensor setup failed.");
    setupPressureSensor() || error("Pressure sensor setup failed.");
}

// runs continuously
void loop() {
    for (int i = 0; i < 15; i++) { // print temp every second for 15 seconds, then end
        double kelvin = getTemperature();
        double farenheit = toFarenheit(kelvin);
        Serial.print("T = ");
        Serial.print(farenheit);
        Serial.print(" °F\t\t");

        double mb = getPressure();
        Serial.print("P = ");
        Serial.println(mb);
        Serial.print(" mb");

        delay(1000);
    }

    end();
}

void end() { while (true) delay(1000); }

bool error(char *msg) {
    Serial.print("Error: ");
    Serial.println(msg);

    end();
    return false;
}
