/*
 * NEAR SPACE BALLOON PROJECT
 * FLIGHT COMPUTER CODE
 *
 * GRINNELL SPACE EXPLORATION AGENCY
 *
 * © 2016.  All Rights Reserved.
 */

#include "temp.h"

#define TMP102_ADDRESS 0x48 // I2C address for sensor
#define K_OFFSET 273.15 // 0°C in K

bool setupTemperatureSensor() {
    Wire.begin();
    return true;
}

double getTemperature() {
    Wire.requestFrom(TMP102_ADDRESS, 2);  // 2 is number of bytes requested

    byte MSB = Wire.read();
    byte LSB = Wire.read();

    //it's a 12-bit int, using two's complement for negative
    int temperatureSum = ((MSB << 8) | LSB) >> 4; 

    double celsius = temperatureSum * 0.0625;
    double kelvin = celsius + K_OFFSET;

    return kelvin;
}

double toCelsius(double kelvin) {
    return kelvin - K_OFFSET;
}

double toFarenheit(double kelvin) {
    return (kelvin - K_OFFSET) * 1.8 + 32;
}
