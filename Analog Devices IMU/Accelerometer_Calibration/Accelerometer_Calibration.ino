//Accelerometer Calibration

#include <SPI.h>

const int CS = 22;

float xmax = -2;  float xmin = 2;
float ymax = -2;  float ymin = 2;
float zmax = -2;  float zmin = 2;

#define XACCL_OUT      0x0A
#define YACCL_OUT      0x0C
#define ZACCL_OUT      0x0E

#define SUPPLYBITS      12
#define ACCBITS         14
#define TEMPBITS        12
#define GYROBITS        14
#define ROLLBITS        13
#define PITCHBITS       13

#define ACCSCALE        0.0006

#define ACCEL_X_OFFSET ((ACCEL_X_MIN + ACCEL_X_MAX) / 2.0f)
#define ACCEL_Y_OFFSET ((ACCEL_Y_MIN + ACCEL_Y_MAX) / 2.0f)
#define ACCEL_Z_OFFSET ((ACCEL_Z_MIN + ACCEL_Z_MAX) / 2.0f)


void setup() {
  
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE3);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  
  Serial.begin(57600);
  
}

void loop() {
  
  // Read Accelerometer Values
  float accelx = (readreg(ACCBITS, XACCL_OUT));
  float accely = (readreg(ACCBITS, YACCL_OUT));
  float accelz = (readreg(ACCBITS, ZACCL_OUT));
  accelx = (twoscomptransform(ACCBITS, accelx));
  accely = (twoscomptransform(ACCBITS, accely));
  accelz = (twoscomptransform(ACCBITS, accelz));
  accelx *= ACCSCALE;  
  accely *= ACCSCALE;
  accelz *= ACCSCALE;
  Serial.print(accelx);  Serial.print(", ");  Serial.print(accely);
  Serial.print(", ");  Serial.print(accelz);
  
  Serial.print("         ");
  
  if(accelx < xmin){
    xmin = accelx;
  }
  else if(accelx > xmax){
    xmax = accelx;
  }
  
  if(accely < ymin){
    ymin = accely;
  }
  else if(accely > ymax){
    ymax = accely;
  }
  
  if(accelz < zmin){
    zmin = accelz;
  }
  else if(accelz > zmax){
    zmax = accelz;
  }
  
  Serial.print(xmin);  Serial.print("/");  Serial.print(xmax);  Serial.print("    ");
  Serial.print(ymin);  Serial.print("/");  Serial.print(ymax);  Serial.print("    ");
  Serial.print(zmin);  Serial.print("/");  Serial.println(zmax);
  
  
  
  
}
