#include <SPI.h>
#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>
Adafruit_GPS GPS(&Serial1);
#define GPSECHO  true
boolean usingInterrupt = false;
void useInterrupt(boolean);
uint32_t timer = millis();

void setup() {
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PGCMD_ANTENNA);
  useInterrupt(true);
  
  Serial.begin(57600);
  Serial.println("latitude,longitude,altitude(m)");
}

void loop() {

    if (! usingInterrupt) {
    // read data from the GPS in the 'main loop'
    char c = GPS.read();
    // if you want to debug, this is a good time to do it!
    
  }
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))
    return;
  }
  
    
    if (GPS.fix) {
      delay(10000);
      Serial.print(GPS.latitudeDegrees, 4);
      Serial.print(", "); 
      Serial.print(GPS.longitudeDegrees, 4);
      Serial.print(", ");
      Serial.println(GPS.altitude);
    
  }
}
