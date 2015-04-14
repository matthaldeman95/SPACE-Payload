/* Combined Payload V4 Test 

*/

//GPS Variables / Libraries 
#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>
Adafruit_GPS GPS(&Serial1);
#define GPSECHO  true
boolean usingInterrupt = false;
void useInterrupt(boolean);
uint32_t timer = millis();

//Geiger Variables
String GeigerString;

//Information for ADIS16300

#include <SPI.h>

//Registers used
#define SUPPLY_OUT     0x02
#define GYRO_OUT       0x04
#define XACCL_OUT      0x0A
#define YACCL_OUT      0x0C
#define ZACCL_OUT      0x0E
#define TEMP_OUT       0x10
#define PITCH_OUT      0x12
#define ROLL_OUT       0x14

//Number of bits of data transferred by registers
#define SUPPLYBITS      12
#define ACCBITS         14
#define TEMPBITS        12
#define GYROBITS        14
#define ROLLBITS        13
#define PITCHBITS       13

//Scale for each data type
#define SUPPLYSCALE     0.00242    //2.42 mV
#define GYROSCALE       0.05       //0.05 degrees / second
#define ACCSCALE        0.0006     //0.6 mg
#define TEMPSCALE       0.14       //0.14 degrees C, 0 corresponds to 25 degrees
#define ROLLSCALE       0.044      //0.044 degrees
#define PITCHSCALE      0.044      //0.044 degrees     

const int CS = 22;

//Magnetometer Pins / Calibration

#include <math.h>

#define MAGN_X_MIN ((float) -0.11)
#define MAGN_X_MAX ((float) 0.45)
#define MAGN_Y_MIN ((float) -0.94)
#define MAGN_Y_MAX ((float) 0.29)
#define MAGN_Z_MIN ((float) -0.81)
#define MAGN_Z_MAX ((float) 0.47)

#define MAGN_X_OFFSET ((MAGN_X_MIN + MAGN_X_MAX) / 2.0)
#define MAGN_Y_OFFSET ((MAGN_Y_MIN + MAGN_Y_MAX) / 2.0)
#define MAGN_Z_OFFSET ((MAGN_Z_MIN + MAGN_Z_MAX) / 2.0)





void setup() {
  
  //Inititalize SPI pins and communication
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE3);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  
  //Initialize Serial Ports  
  Serial2.begin(9600);    //Geiger Serial Port
  Serial.begin(57600);   //Openlog or Computer Serial Port
  
  //GPS Setup
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PGCMD_ANTENNA);
  useInterrupt(true);
  
}

void loop() {
  delay(1000);  //Time between measurements
  
      readGPS();
  
      printGPS();
      
  delay(1000);
      
      readADISSensors();
      
  delay(1000);
      
       readMag();
       
  delay(1000);
  
      readGeiger();
  
}
