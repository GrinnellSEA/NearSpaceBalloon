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
#include "aprs.h"
#include "rtty.h"

byte value = 0;

// runs once at start
void setup() {
    Serial.begin(9600); // begin logging

    setupRadio();
    setupTemperatureSensor() || error("Temperature sensor setup failed.");
    setupPressureSensor() || error("Pressure sensor setup failed.");

    ptt(true);
}

void loop2() {
    send_packet(getTemperature(), getPressure());
    delay(1000);
}

// runs continuously
void loop() {
    char msg[80];
    int temp = (int) getTemperature();
    int pres = (int) getPressure();
    Serial.print(temp);
    sprintf(msg, "GSEA~S %ld~T %d~P %d~\n", millis()/1000, temp, pres);
    send_rtty_string(msg);
    delay(5000);
}

void end() { while (true) delay(1000); }

bool error(char *msg) {
    Serial.print("Error: ");
    Serial.println(msg);

    end();
    return false;
}
