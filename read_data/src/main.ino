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

    double temperature = map(temp_int, 0, 255, 0, 51);
    double pressure = map(pres_int, 0, 255, 950, 1050);
    double voltage = map(vcc_int, 0, 255, 2000, 7100);
    int minutes = address / 3 * 5;
   
    Serial.print(minutes);
    Serial.print(" minutes: \t");
    Serial.print(temperature);
    Serial.print(" °F\t");
    Serial.print(pressure);
    Serial.print(" mb\t");
    Serial.print(voltage);
    Serial.print(" V\n");

    address += 3;
}

void end() { while(true) delay(10e3); }
