byte ZERO = 0x00;
byte incomingbyte;
long int j=0,k=0,count=0,i=0x0000;
uint8_t MH,ML;
boolean EndFlag=0;

void setup(){
  Serial.begin(115200);
  
  
}

void loop(){
  
  byte a[32];
  int ii;
  Serial1.begin(115200);
  delay(200);
  SendResetCmd();
  delay(2000);
  SetBaudRateCmd(0x2A);
  delay(100);
  Serial1.begin(38400);
  delay(100);
  SetImageSizeCmd(0x1D);
  delay(100);
  SendTakePhotoCmd();
  delay(3000);
  
  while(Serial1.available()>0)
  {
     incomingbyte=Serial1.read();
  }
  
  while(!EndFlag)
  {
    j=0;
    k=0;
    count=0;
    SendReadDataCmd();
    delay(5);
    while(Serial1.available()>0)
    {
      incomingbyte=Serial1.read();
      k++;
      delayMicroseconds(100); 
      if((k>5)&&(j<32)&&(!EndFlag))
      {
        a[j]=incomingbyte;
        if((a[j-1]==0xFF)&&(a[j]==0xD9))     //tell if the picture is finished
        EndFlag=1;
        j++;
       count++; 
      }
     }
  
  
  for(j=0;j<count;j++)
    {
      if(a[j]<0x10)  Serial.print("0");
      Serial.print(a[j],HEX);           // observe the image through serial port
      Serial.print(" ");
    }
    
    for(ii=0; ii<count; ii++)
    Serial.write(a[11]);
    Serial.println();
    
    
  }
  
}
  
