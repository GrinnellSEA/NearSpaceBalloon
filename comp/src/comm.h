/*
 * NEAR SPACE BALLOON PROJECT
 * COMMUNICATION CODE
 *
 * GRINNELL SPACE EXPLORATION AGENCY
 *
 * (c) 2015.  All Rights Reserved.
 */

#define RADIOPIN 9 // the pin to send data on
#define BITRATE (1000 / 50) // n baud
#define BASE 100 // base frequency
#define RANGE 10 // amount to vary frequency by 

void setupComms();
void send(int data);
void setPWMFrequency(int pin, int divisor);
void sendByte(byte d);
void hadamard_enc(byte msg, byte enc[]);
byte hadamard_dec(byte msg[]);
