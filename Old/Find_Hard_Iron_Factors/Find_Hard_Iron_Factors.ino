int sensorPin0 = A1; // X out 
int sensorPin1 = A2; // Y out
int sensorPin2 = A3; // Z out
int sensorPin3 = A0; // Vref
float sensorValue[3];

float minx = 150000;  float maxx = -150000;
float miny = 150000;  float maxy = -150000;
float minz = 150000;  float maxz = -150000;


void setup() {
  //initialize 9600 baud serial communications for arduino serial monitor
  Serial.begin(57600);
}

void loop() {
  //Read sensors using analogRead() function.
  //Mag Field (Gauss) = (OutputVoltage-ReferenceVoltage)*(conversion factor = 2.5/512)
  // 1/512 is Arduino ADC resolution
  // +-2.5 is HMC2003 max voltage.
  float xval = (analogRead(sensorPin0)-analogRead(sensorPin3))*(2.5/512)*100000;
  float yval = (analogRead(sensorPin1)-analogRead(sensorPin3))*(2.5/512)*100000;
  float zval = (analogRead(sensorPin2)-analogRead(sensorPin3))*(2.5/512)*100000;
  
  if(xval < minx){
    minx = xval;
  }
  else if(xval > maxx){
    maxx = xval;
  }
  
  if(yval < miny){
    miny = yval;
  }
  else if(yval > maxy){
    maxy = yval;
  }
  
  if(zval < minz){
    minz = zval;
  }
  else if(zval > maxz){
    maxz = zval;
  }
  
  
  Serial.print("X max, min: ");  Serial.print(maxx);  Serial.print(", ");  Serial.print(minx);
  Serial.print(", Y max, min: ");  Serial.print(maxy);  Serial.print(", ");  Serial.print(miny);
  Serial.print(", Z max, min: ");  Serial.print(maxz);  Serial.print(", ");  Serial.println(minz);
  
}
