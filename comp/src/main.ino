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
#include "gps.h"

#define INTERVAL 10000 // how often to send radio signals

ProbeInfo info;
unsigned long previous = 0;

// runs once at start
void setup() {
    setupRadio();
    setupGPS();
    setupTemperatureSensor();
    setupPressureSensor();
    ptt(true);
}

void loop2() {
    send_packet(getTemperature(), getPressure());
    delay(1000);
}

// runs continuously
void loop() {
    getGPSData(&info);

    unsigned long current = millis();

    if (current - previous >= INTERVAL) {
        previous = current;

        char msg[80];

        int temp = (int) (10*getTemperature());
        int pres = (int) getPressure();
        long lat = (long) (10000 * info.latitude);
        long lon = (long) (10000 * info.longitude);
        int alt = (int) (10 * info.altitude);

        sprintf(msg, "GSEA~S %ld~T %d~P %d~X %ld~Y %ld~A %d~\n", 
                millis()/1000, 
                temp, 
                pres,
                lon,
                lat,
                alt
            );

        send_rtty_string(msg);
    }
}

void end() { while (true) delay(1000); }
