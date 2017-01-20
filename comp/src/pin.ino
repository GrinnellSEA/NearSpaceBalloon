/*
 * NEAR SPACE BALLOON PROJECT
 * FLIGHT COMPUTER CODE
 *
 * GRINNELL SPACE EXPLORATION AGENCY
 *
 * © 2016.  All Rights Reserved.
 */

#include <pins_arduino.h>
#include <Arduino.h>
#include "pin.h"

// This is a digitalWrite() replacement that does not disrupt
// timer 2.
void pin_write(byte pin, byte val) {
    byte bit = digitalPinToBitMask(pin);
    byte port = digitalPinToPort(pin);
    volatile byte *out;

    if (port == NOT_A_PIN) return;

    out = portOutputRegister(port);

    if (val == LOW) {
        byte oldSREG = SREG;
        cli();
        *out &= ~bit;
        SREG = oldSREG;
    } else {
        byte oldSREG = SREG;
        cli();
        *out |= bit;
        SREG = oldSREG;
    }
}
