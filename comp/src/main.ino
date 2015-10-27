/*
 * NEAR SPACE BALLOON PROJECT
 * FLIGHT COMPUTER CODE
 *
 * GRINNELL SPACE EXPLORATION AGENCY
 *
 * (c) 2015.  All Rights Reserved.
 */

#include "comm.c++"
#include "sensors.c++"

// runs once at start
void setup() {
	setupComms();
}

// runs continuously
void loop() { 
	sendSensorData();

	end(); // for debugging TODO remove 
}

/*
 * Send sensor data back to earth
 */
void sendSensorData() {
	// collect sesnsor data
	double lat = getLatitude();
	double lon = getLongitude();
	double alt = getAltitude();
	double tmp = getTemperature();
	double prs = getPressure();
	// format data for sending
	int f_lat = map(lat, 40.0, 46.5335, 0, 65535);
	int f_lon = map(lat, -88.0, -94.5535, 0, 65525);
	int f_alt = map(alt, 0, 2, 0, 1);
	int f_tmp = map(tmp, 0, 1, 0, 100);
	int f_prs = map(prs, 0, 1, 0, 1000000);

	// send data
	send(f_lat);
	send(f_lon);
	send(f_alt);
	send(f_tmp);
	send(f_prs);
}	

void end() { while (true) delay(1000); }
