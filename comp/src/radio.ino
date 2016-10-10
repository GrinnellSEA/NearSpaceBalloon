/*
 * NEAR SPACE BALLOON PROJECT
 * RADIO CODE
 *
 * GRINNELL SPACE EXPLORATION AGENCY
 *
 * © 2015.  All Rights Reserved.
 */

#define RADIO_PIN 9
#define ENABLE_PIN 8
#define CRC16 0x1021

#include <string.h>

char datastring[80];

bool setupRadio() {
    pinMode(RADIO_PIN, OUTPUT);

    // set high PWM frequency
    TCCR1B = TCCR1B & 0b11111000 | 0x01; // CHANGE THIS IF RADIO_PIN CHANGES

    pinMode(ENABLE_PIN, OUTPUT);
    digitalWrite(ENABLE_PIN, HIGH);

    return true;
}

void ptt(bool on) {
    digitalWrite(ENABLE_PIN, on);
    if (on) delay(25); // wait 25ms for radio to turn on
}
