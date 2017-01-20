/*
 * NEAR SPACE BALLOON PROJECT
 * FLIGHT COMPUTER CODE
 *
 * GRINNELL SPACE EXPLORATION AGENCY
 *
 * © 2017.  All Rights Reserved.
 */

#ifndef APRS_H_
#define APRS_H_

/**
 * Send the APRS packet with location and sensor information.
 */
void send_packet(double pressure, double temperature);

#endif // APRS_H_
