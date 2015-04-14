void readADISSensors(){

// Read Gyro Values
  Serial.print("Gyro (degrees/second): ");
  float gyro = (readreg(GYROBITS, GYRO_OUT));
  gyro = (twoscomptransform(GYROBITS, gyro));
  Serial.println(gyro * GYROSCALE);
  
  // Read Accelerometer Values
  Serial.print("Accel (X,Y,Z) (in g): ");
  float accelx = (readreg(ACCBITS, XACCL_OUT));
  float accely = (readreg(ACCBITS, YACCL_OUT));
  float accelz = (readreg(ACCBITS, ZACCL_OUT));
  accelx = (twoscomptransform(ACCBITS, accelx));
  accely = (twoscomptransform(ACCBITS, accely));
  accelz = (twoscomptransform(ACCBITS, accelz));
  Serial.print(accelx * ACCSCALE);  Serial.print(", ");  Serial.print(accely * ACCSCALE);  
  Serial.print(", ");     Serial.println(accelz * ACCSCALE); 
 
  // Read Roll
  Serial.print("Roll: ");
  float roll = (readreg(ROLLBITS, ROLL_OUT));
  roll = (twoscomptransform(ROLLBITS, roll));
  Serial.print(roll * ROLLSCALE); 
  
  // Read Pitch
  Serial.print(", Pitch: ");
  float pitch = (readreg(PITCHBITS, PITCH_OUT));
  pitch = (twoscomptransform(PITCHBITS, pitch));
  Serial.print(pitch * PITCHSCALE);  Serial.println(",");
  
}


  
  
//Program to read register reg with number of bits nbits
unsigned int readreg(unsigned char nbits, unsigned char reg){
  unsigned char upper, lower, mask;
  
  digitalWrite(CS, LOW);
  SPI.transfer(reg);
  SPI.transfer(0x00);
  digitalWrite(CS, HIGH);
  delay(100);
  digitalWrite(CS, LOW);
  upper = SPI.transfer(0x00);
  lower = SPI.transfer(0x00);
  digitalWrite(CS, HIGH);
  
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
  

