/* Combined Payload Code V1 */

#include <SPI.h>


//Magnetometer Pins 

const int xmag = A1;
const int ymag = A2;
const int zmag = A3;
const int magref = A0;
float magval[2];

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

void setup() {
  //Inititalize SPI pins and communication
  pinMode(53, OUTPUT);
  digitalWrite(53, HIGH);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE3);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  
  //Initialize Serial Ports
  Serial1.begin(9600);  //Geiger Serial Port
  Serial.begin(57600);   //Openlog or Computer Serial Port
  
  

}

void loop() {
  delay(1000);  // Time between measurements
  
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
 
 
 //Read Magnetometer Values
 //Mag Field (Gauss) = (OutputVoltage-ReferenceVoltage)*(conversion factor = 2.5/512)
 
 Serial.print("Magnetometer (X,Y,Z) (Gauss???): ");
 magval[0] = (analogRead(xmag)-analogRead(magref))*(2.5/512)*100000;
 magval[1] = (analogRead(ymag)-analogRead(magref))*(2.5/512)*100000;    
 magval[2] = (analogRead(zmag)-analogRead(magref))*(2.5/512)*100000;     
 Serial.print(magval[0]);  Serial.print(", ");  Serial.print(magval[1]);  Serial.print(", ");
 Serial.println(magval[2]);
 
}
