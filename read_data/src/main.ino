/*
 * NEAR SPACE BALLOON
 * FLIGHT COMPUTER DATA COLLECTION
 *
 * GRINNELL SPACE EXPLORATION AGENCY
 *
 * © 2016.  All Rights Reserved.
 */

#include <EEPROM.h>

int address = 0;
int max_addr;

void setup() {
   Serial.begin(9600); 

   max_addr = EEPROM.length();
}

void loop() {
    byte temp_int = EEPROM.read(address + 0);
    byte pres_int = EEPROM.read(address + 1);
    byte vcc_int = EEPROM.read(address + 2);

    if (temp_int == 0 && pres_int == 0 && vcc_int == 0) // end of data
        end();

    double temperature = memDecompress(temp_int, 0, 102);
    double pressure = memDecompress(pres_int, 950, 1050);
    double voltage = memDecompress(vcc_int, 2.0, 7.1);
    int minutes = address / 3 * 5;
   
    Serial.print(minutes);
    Serial.print(" seconds: \t");
    Serial.print(temperature);
    Serial.print(" °F \t");
    Serial.print(pressure);
    Serial.print(" mb \t");
    Serial.print(voltage);
    Serial.print(" V\r\n");

    address += 3;
}

void end() { while(true) delay(10e3); }

double memDecompress(int value, double out_min, double out_max) {
    return ((double) value) * (out_max - out_min) / 255 + out_min;
}
