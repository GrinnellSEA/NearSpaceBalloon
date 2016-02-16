/*
 * NEAR SPACE BALLOON PROJECT
 * FLIGHT COMPUTER CODE
 *
 * GRINNELL SPACE EXPLORATION AGENCY
 *
 * (c) 2016.  All Rights Reserved.
 */

#include <SFE_BMP180.h>
#include <Wire.h>

#ifndef PRESSURE_H_
#define PRESSURE_H_

/**
 * Reads current pressure from sensor.
 *
 * @return current pressure, in millibars.
 */
double getPressure();

#endif // PRESSURE_H_
