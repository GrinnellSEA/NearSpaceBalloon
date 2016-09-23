/*
 * NEAR SPACE BALLOON PROJECT
 * FLIGHT COMPUTER CODE
 *
 * GRINNELL SPACE EXPLORATION AGENCY
 *
 * © 2016.  All Rights Reserved.
 */

#include "temp.h"
#include "pressure.h"
#include "radio.h"

byte value = 0;

// runs once at start
void setup() {
    Serial.begin(9600); // begin logging

    setupRadio();
    //setupTemperatureSensor() || error("Temperature sensor setup failed.");
    //setupPressureSensor() || error("Pressure sensor setup failed.");
}

// runs continuously
void loop() {
    setRadio(value++);
    value = value % 256;
    delay(100);
}

void end() { while (true) delay(1000); }

bool error(char *msg) {
    Serial.print("Error: ");
    Serial.println(msg);

    end();
    return false;
}
