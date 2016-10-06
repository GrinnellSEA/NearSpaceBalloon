/*
 * NEAR SPACE BALLOON PROJECT
 * RADIO CODE
 *
 * GRINNELL SPACE EXPLORATION AGENCY
 *
 * © 2015.  All Rights Reserved.
 */

#ifndef RADIO_H_
#define RADIO_H_

/**
 * Set up radio for transmission
 *
 * @return success
 */
bool setupRadio();

/**
 * Send a RTYY string.
 * The function calculates the checksum and appends the checksum string.
 */
void sendString(char * msg);

#endif // RADIO_H_
