//Magnetometer Reader

//Reads sensor values in through pins A0-A4 using AnalogRead(). 
//Converts values to Gauss. 
//Stores values in sensorValue[].
//Prints values in sensorValue[] to serial line.

int sensorPin0 = A1; // X out 
int sensorPin1 = A2; // Y out
int sensorPin2 = A3; // Z out
int sensorPin3 = A0; // Vref
float sensorValue[3];

void setup() {
  //initialize 9600 baud serial communications for arduino serial monitor
  Serial.begin(57600);
}


void loop() {
  //Read sensors using analogRead() function.
  //Mag Field (Gauss) = (OutputVoltage-ReferenceVoltage)*(conversion factor = 2.5/512)
  // 1/512 is Arduino ADC resolution
  // +-2.5 is HMC2003 max voltage.
  sensorValue[0] = (analogRead(sensorPin0)-analogRead(sensorPin3))*(2.5/512)*100000;
  sensorValue[1] = (analogRead(sensorPin1)-analogRead(sensorPin3))*(2.5/512)*100000;
  sensorValue[2] = (analogRead(sensorPin2)-analogRead(sensorPin3))*(2.5/512)*100000;
  sensorValue[3] = (analogRead(sensorPin3)-analogRead(sensorPin3))*(2.5/512)*100000;
  Serial.print( "xval, ");
  Serial.print(sensorValue[0]);
  Serial.print(",yval, ");
  Serial.println(sensorValue[1]);
}
