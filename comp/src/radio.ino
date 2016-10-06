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

void sendString(char * msg) {
    Serial.print(msg);
    snprintf(datastring, 80, msg);
    Serial.print(datastring);
    short checksum = calculateChecksum(datastring);
    Serial.println(checksum);
    char checksum_str[6];
    sprintf(checksum_str, "*%04X\n", checksum);
    Serial.print(checksum_str);
    strcat(datastring, checksum_str);
    Serial.print(datastring);

    
    for (char * c = datastring; *c != '\0'; c++) 
        sendByte(*c);
}

void sendByte(byte b) {
    sendBit(0); // start bit

    for (byte i = 0; i < 7; i++) {
        if (b & 1)
            sendBit(1);
        else
            sendBit(0);

        b = b >> 1; // next bit
    }

    sendBit(1); // stop bit
    sendBit(1);
}

void sendBit(byte bit) {
    analogWrite(RADIO_PIN, bit ? 110 : 100);
    // two-step delay for more accuracy
    delayMicroseconds(10000);
    delayMicroseconds(10150);
}

short calculateChecksum(char * str) {
    byte i;
    byte count = 80;
    short crc = 0;

    do {
        crc = crc ^ (int) *str++ << 8;
        i = 8;

        do {
            if (crc & 0x8000)
                crc = crc << 1 ^ 0x1021;
            else
                crc = crc << 1;
        } while (--i);
    } while (--count);

    return crc;
}



