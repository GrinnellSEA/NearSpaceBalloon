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

bool setupRadio() {
    pinMode(RADIO_PIN, OUTPUT);

    // set high PWM frequency
    TCCR1B = TCCR1B & 0b11111000 | 0x01; // CHANGE THIS IF RADIO_PIN CHANGES

    pinMode(ENABLE_PIN, OUTPUT);
    digitalWrite(ENABLE_PIN, HIGH);

    return true;
}

void setRadio(bool on) {
    if (on)
        analogWrite(RADIO_PIN, 110);
    else
        analogWrite(RADIO_PIN, 100);
}
