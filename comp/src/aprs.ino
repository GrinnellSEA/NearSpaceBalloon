/*
 * NEAR SPACE BALLOON PROJECT
 * FLIGHT COMPUTER CODE
 *
 * GRINNELL SPACE EXPLORATION AGENCY
 *
 * © 2016.  All Rights Reserved.
 */

#include "radio_config.h"
#include "ax25.h"
#include "aprs.h"
#include <stdio.h>
#include <stdlib.h>
#include <Arduino.h>

void send_packet(double pressure, double temperature) {
    char status[12];
    const struct s_address addresses[] = {
        {D_CALLSIGN, D_CALLSIGN_ID},
        {S_CALLSIGN, S_CALLSIGN_ID},
#ifdef DIGI_PATH1
        {DIGI_PATH1, DIGI_PATH1_TTL},
#endif
#ifdef DIGI_PATH2
        {DIGI_PATH2, DIGI_PATH2_TTL},
#endif
    };

    ax25_send_header(addresses, sizeof(addresses)/sizeof(s_address));
    ax25_send_byte('/');
    ax25_send_string("101530z"); // 10th day of month, 15:30 UTC
    ax25_send_byte('h');
    ax25_send_string("44 LAT");
    ax25_send_byte('/');
    ax25_send_string("-92 LON");
    ax25_send_byte('0');
    snprintf(status, 4, "%03d", 0); // course
    ax25_send_string(status);
    ax25_send_byte('/');
    snprintf(status, 4, "%03d", 1); // speed
    ax25_send_string(status);
    ax25_send_string("/A=");
    snprintf(status, 7, "%06ld", 300); // altitude
    ax25_send_string(status);
    ax25_send_string("/Te=");
    snprintf(status, 6, "%d", temperature); 
    ax25_send_string(status);
    ax25_send_string("/V=");
    snprintf(status, 6, "%d", 5.0); // voltage
    ax25_send_string(status);
    ax25_send_string("/P=");
    ax25_send_string(status);
    snprintf(status, 6, "%d", pressure); 
    ax25_send_footer();
    ax25_flush_frame();
}
