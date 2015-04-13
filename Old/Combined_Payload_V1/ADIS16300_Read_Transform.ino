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

