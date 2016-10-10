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
 * Start or stop the radio transmission.
 */
void ptt(bool on);

#endif // RADIO_H_
