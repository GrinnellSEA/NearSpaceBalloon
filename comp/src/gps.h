/*
 * NEAR SPACE BALLOON PROJECT
 * FLIGHT COMPUTER CODE
 *
 * GRINNELL SPACE EXPLORATION AGENCY
 *
 * © 2017.  All Rights Reserved.
 */

#ifndef GPS_H_
#define GPS_H_

#define LOW_ALTITUDE 0x03
#define HIGH_ALTITUDE 0x06

typedef struct {
    double latitude;   // decimal degrees
    double longitude;  // decimal degrees
    double altitude;   // meters
    byte satellites;  
    double speed;      // meters per second

} ProbeInfo;

/**
 * Set up GPS sensor. 
 * 
 * @return true if successful, false otherwise.
 */
bool setupGPS();

/**
 * Get current GPS coordinates and store them in given ProbeInfo struct.
 */
void getGPSData(ProbeInfo * info);

#endif // GPS_H_
