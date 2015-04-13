/* Code for the Analog Devices ADIS16300 */

#include <SPI.h>


//Registers used
#define SUPPLY_OUT     0x02
#define GYRO_OUT       0x04
#define XACCL_OUT      0x0A
#define YACCL_OUT      0x0C
#define ZACCL_OUT      0x03
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
#define SUPPLYSCALE     0.00242
#define GYROSCALE       0.05
#define ACCSCALE        0.0006
#define TEMPSCALE       0.14
#define ROLLSCALE       0.044
#define PITCHSCALE      0.044


void setup(){
  pinMode(53, OUTPUT);
  digitalWrite(53, HIGH);
  
  //SPI Mode from the datashet
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE3);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  
  Serial1.begin(9600);
  Serial.begin(9600);
}

void loop(){
  
  delay(1000);
  
  //Read Geiger Counter String
  String GeigerString = "";
  if(Serial1.available() > 0){
    GeigerString = Serial1.readStringUntil('\n');
  }
  
  if(GeigerString != ""){
    Serial.println(GeigerString);
  }
  
  
  // Read Supply Voltage
  Serial.print("Supply: ");
  int supply = (readreg(SUPPLYBITS, SUPPLY_OUT));
  Serial.print(supply * SUPPLYSCALE);
  Serial.println("V");
  
  // Read Gyro Values
  Serial.print("Gyro (degrees/second): ");
  float gyro = (readreg(GYROBITS, GYRO_OUT));
  gyro = (twoscomptransform(GYROBITS, gyro));
  Serial.print(gyro * GYROSCALE);
  
  // Read Accelerometer Values
  Serial.print("Accel (X,Y,Z) (m/s^2): ");
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
  Serial.println("C");
  
  // Read Roll
  Serial.print("Roll: ");
  float roll = (readreg(ROLLBITS, ROLL_OUT));
  roll = (twoscomptransform(ROLLBITS, roll));
  Serial.println(roll * ROLLSCALE);  
  
  // Read Pitch
  float pitch = (readreg(PITCHBITS, PITCH_OUT));
  pitch = (twoscomptransform(PITCHBITS, pitch));
  Serial.print(pitch * PITCHSCALE);  Serial.print(",");
  
}

//Program to read register reg with number of bits nbits
unsigned int readreg(unsigned char nbits, unsigned char reg){
  unsigned char upper, lower, mask;
  
  digitalWrite(53, LOW);
  SPI.transfer(reg);
  SPI.transfer(0x00);
  digitalWrite(53, HIGH);
  delay(100);
  digitalWrite(53, LOW);
  upper = SPI.transfer(0x00);
  lower = SPI.transfer(0x00);
  digitalWrite(53, HIGH);
  
  mask = 0xFF >> (16 - nbits);
  
  return   ( ( upper & mask) << 8 | lower)  ;
}

//Perform two complement transformation on data
double twoscomptransform(unsigned char nbits, unsigned int num){
  unsigned int mask, padding;
  // select correct mask
  mask = 1 << (nbits -1);
  
  // if MSB is 1, then number is negative, so invert it and add one
  // if MSB is 0, then just return the number 
  return (num & mask)?( -1.0 * (~(num | 0xFF << nbits)  + 1) ):( 1.0 * num );
}
  
 

  





