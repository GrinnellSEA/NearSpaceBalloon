/*
 * NEAR SPACE BALLOON PROJECT
 * RADIO CODE
 *
 * GRINNELL SPACE EXPLORATION AGENCY
 *
 * © 2015.  All Rights Reserved.
 */

#include "radio.h"
#include "pin.h"
#include "radio_config.h"

bool setupRadio() {
    pinMode(AUDIO_PIN, OUTPUT);
    pinMode(PTT_PIN, OUTPUT);

    return true;
}

void ptt(bool on) {
    pin_write(AUDIO_PIN, 0);
    pin_write(PTT_PIN, on);
    if (on) delay(1000); // wait for radio to turn on
}
