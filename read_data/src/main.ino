/*
 * NEAR SPACE BALLOON
 * FLIGHT COMPUTER DATA COLLECTION
 *
 * GRINNELL COLLEGE
 * 2016.
 */

#include <EEPROM.h>

void setup() {
   Serial.begin(9600); 
}

void loop() {
    byte temp_int = EEPROM.read(0);
    byte pres_int = EEPROM.read(1);
    byte vcc_int = EEPROM.read(2);
    byte time_int = EEPROM.read(3);

    double temperature = map(temp_int, 0, 255, 0, 71);
    double pressure = map(pres_int, 0, 255, 950, 1050);
    double voltage = map(vcc_int, 0, 255, 2.0, 7.1);
    int minutes = time_int * 5;
   
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °F\n");

    Serial.print("Pressure: ");
    Serial.print(pressure);
    Serial.print(" mb\n");

    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.print(" V\n");

    Serial.print("Total time: ");
    Serial.print(minutes);
    Serial.print(" minutes\n");

    end();
}

void end() { while(true) delay(10e3); }
