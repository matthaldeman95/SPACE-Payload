void SendResetCmd()
{
    Serial1.write(0x56);
    Serial1.write(0x00);
    Serial1.write(0x26);
    Serial1.write(0x00);
}

/*************************************/
/* Set ImageSize :
/* <1> 0x22 : 160*120
/* <2> 0x11 : 320*240
/* <3> 0x00 : 640*480
/* <4> 0x1D : 800*600
/* <5> 0x1C : 1024*768
/* <6> 0x1B : 1280*960
/* <7> 0x21 : 1600*1200
/************************************/
void SetImageSizeCmd(byte Size)
{
    Serial1.write(0x56);
    Serial1.write(0x00);  
    Serial1.write(0x54);
    Serial1.write(0x01);
    Serial1.write(Size);
}

/*************************************/
/* Set BaudRate :
/* <1>¡¡0xAE  :   9600
/* <2>¡¡0x2A  :   38400
/* <3>¡¡0x1C  :   57600
/* <4>¡¡0x0D  :   115200
/* <5>¡¡0xAE  :   128000
/* <6>¡¡0x56  :   256000
/*************************************/
void SetBaudRateCmd(byte baudrate)
{
    Serial1.write(0x56);
    Serial1.write(0x00);
    Serial1.write(0x24);
    Serial1.write(0x03);
    Serial1.write(0x01);
    Serial1.write(baudrate);
}
 
void SendTakePhotoCmd()
{
    Serial1.write(0x56);
    Serial1.write(0x00);
    Serial1.write(0x36);
    Serial1.write(0x01);
    Serial1.write(0x00); 
}
 
void SendReadDataCmd()
{
    MH=i/0x100;
    ML=i%0x100;
    Serial1.write(0x56);
    Serial1.write(0x00);
    Serial1.write(0x32);
    Serial1.write(0x0c);
    Serial1.write(0x00);
    Serial1.write(0x0a);
    Serial1.write(0x00);
    Serial1.write(0x00);
    Serial1.write(MH);
    Serial1.write(ML);
    Serial1.write(0x00);
    Serial1.write(0x00);
    Serial1.write(0x00);
    Serial1.write(0x20);
    Serial1.write(0x00);
    Serial1.write(0x0a);
    i+=0x20;
}
 
void StopTakePhotoCmd()
{
    Serial1.write(0x56);
    Serial1.write(0x00);
    Serial1.write(0x36);
    Serial1.write(0x01);
    Serial1.write(0x03);
}

