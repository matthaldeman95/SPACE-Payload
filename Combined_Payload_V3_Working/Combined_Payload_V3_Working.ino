// Testing Github 

/* Combined Payload Code V1 */

//Test

//GPS Variables / Libraries
#include <SPI.h>
#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>
Adafruit_GPS GPS(&Serial3);
#define GPSECHO  true
boolean usingInterrupt = false;
void useInterrupt(boolean);
uint32_t timer = millis();

//Geiger Variables
String GeigerString;

//Magnetometer Pins 

const int xmag = A1;
const int ymag = A2;
const int zmag = A3;
const int magref = A0;
float xmagval;  float ymagval;  float zmagval;  

//Information for ADIS16300

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
  
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PGCMD_ANTENNA);
  useInterrupt(true);
  
  

  
  
  

}

void loop() {
   delay(1000); // Time between measurements
  
  //Read GPS Data
  
  if (! usingInterrupt) {
    // read data from the GPS in the 'main loop'
    char c = GPS.read();
    // if you want to debug, this is a good time to do it!
    
  }
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))
    return;
  }
  
    
    Serial.print("\nTime: ");
    Serial.print((GPS.hour, DEC) - 5); Serial.print(':');
    Serial.print(GPS.minute, DEC); Serial.print(':');
    Serial.print(GPS.seconds, DEC); Serial.print('.');
    Serial.println(GPS.milliseconds);
    
    Serial.print("Fix: "); Serial.print((int)GPS.fix);
    Serial.print(" quality: "); Serial.println((int)GPS.fixquality); 
    if (GPS.fix) {
      Serial.print("Location: ");
      Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
      Serial.print(", "); 
      Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
      Serial.print("Location (in degrees, works with Google Maps): ");
      Serial.print(GPS.latitudeDegrees, 4);
      Serial.print(", "); 
      Serial.println(GPS.longitudeDegrees, 4);
      
      Serial.print("Angle: "); Serial.println(GPS.angle);
      Serial.print("Altitude (m): "); Serial.println(GPS.altitude);
    
  }
  
 
  
  
   //Read Geiger Counter
   
  delay(1000);
  GeigerString = "";
  if(Serial2.available() > 0){
    
    GeigerString = Serial2.readStringUntil('\n');  
    if(GeigerString != ""){
      Serial.println(GeigerString);
    }
  }
  
  delay(1000);
  
  /*
  
  //Read Magnetometer Values
 //Mag Field (Gauss) = (OutputVoltage-ReferenceVoltage)*(conversion factor = 2.5/512)
 
 Serial.print("Magnetometer (X,Y,Z): ");
 xmagval = (analogRead(A1)-analogRead(A0))*(2.5/512)*100000;
 ymagval = (analogRead(A2)-analogRead(A0))*(2.5/512)*100000;
 zmagval = (analogRead(A3)-analogRead(A0))*(2.5/512)*100000;
 Serial.print(xmagval);  Serial.print(", ");  Serial.print(ymagval);  Serial.print(", ");
 Serial.println(zmagval);
 
 
  
  //Read ADIS Sensor Registers
  
  // Read Gyro Values
  Serial.print("Gyro (degrees/second): ");
  float gyro = (readreg(GYROBITS, GYRO_OUT));
  gyro = (twoscomptransform(GYROBITS, gyro));
  Serial.print(gyro * GYROSCALE);
  
  // Read Accelerometer Values
  Serial.print(", Accel (X,Y,Z) (in g): ");
  float accelx = (readreg(ACCBITS, XACCL_OUT));
  float accely = (readreg(ACCBITS, YACCL_OUT));
  float accelz = (readreg(ACCBITS, ZACCL_OUT));
  accelx = (twoscomptransform(ACCBITS, accelx));
  accely = (twoscomptransform(ACCBITS, accely));
  accelz = (twoscomptransform(ACCBITS, accelz));
  Serial.print(accelx * ACCSCALE);  Serial.print(", ");  Serial.print(accely * ACCSCALE);  
  Serial.print(", ");     Serial.println(accelz * ACCSCALE); 
  
  // Read Temperature
  Serial.print("Temp: ");
  float temp = (readreg(TEMPBITS, TEMP_OUT));
  temp = (twoscomptransform(TEMPBITS, temp));
  Serial.print((temp * TEMPSCALE) + 25);
  Serial.print("C");
 
  // Read Roll
  Serial.print(";   Roll: ");
  float roll = (readreg(ROLLBITS, ROLL_OUT));
  roll = (twoscomptransform(ROLLBITS, roll));
  Serial.print(roll * ROLLSCALE); 
  
  // Read Pitch
  Serial.print(", Pitch: ");
  float pitch = (readreg(PITCHBITS, PITCH_OUT));
  pitch = (twoscomptransform(PITCHBITS, pitch));
  Serial.print(pitch * PITCHSCALE);  Serial.println(",");
 
 
 
*/
 
 
 
  
}
