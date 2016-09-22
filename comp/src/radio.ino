/*
 * NEAR SPACE BALLOON PROJECT
 * RADIO CODE
 *
 * GRINNELL SPACE EXPLORATION AGENCY
 *
 * © 2015.  All Rights Reserved.
 */

#define RADIO_PIN 9
#define ENABLE_PIN 10

bool setupRadio() {
    pinMode(RADIO_PIN, OUTPUT);
    setPWMFrequency(RADIO_PIN, 1);

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

void setPWMFrequency(byte pin, byte divisor) {
    byte mode;

    if (pin == 5 || pin == 6 || pin == 9 || pin == 10) {
        switch (divisor) {
            case 1:
                mode = 0x01;
                break;
            case 8:
                mode = 0x02;
                break;
            case 64:
                mode = 0x03;
                break;
            case 256:
                mode = 0x04;
                break;
            case 1024:
                mode = 0x05;
                break;
            default:
                return;
        }
 
        if (pin == 5 || pin == 6) {
            TCCR0B = TCCR0B & 0b11111000 | mode;
        } else {
            TCCR1B = TCCR1B & 0b11111000 | mode;
        }
    } else if (pin == 3 || pin == 11) {
        switch (divisor) {
            case 1:
                mode = 0x01;
                break;
            case 8:
                mode = 0x02;
                break;
            case 32:
                mode = 0x03;
                break;
            case 64:
                mode = 0x04;
                break;
            case 128:
                mode = 0x05;
                break;
            case 256:
                mode = 0x06;
                break;
            case 1024:
                mode = 0x7;
                break;
            default:
                return;
        }

        TCCR2B = TCCR2B & 0b11111000 | mode;
    }
}
