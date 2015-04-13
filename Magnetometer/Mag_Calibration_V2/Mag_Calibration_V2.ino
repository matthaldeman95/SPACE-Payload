//Magnetometer Calibration

const int xpin = A1;
const int ypin = A2;
const int zpin = A3;
const int magrefpin = A0;
float magnetom[2];
float magxmax = -2;  float magxmin = 2;  
float magymax = -2;  float magymin = 2;
float magzmax = -2;  float magzmin = 2;


void setup() {
  Serial.begin(57600);
}

void loop() {
  //Mag Field (Gauss) = (OutputVoltage-ReferenceVoltage)*(conversion factor = 2.5/512)
  delay(100);
  magnetom[0] = (analogRead(A1) - analogRead(A0)) * (2.5/512);
  magnetom[1] = (analogRead(A2) - analogRead(A0)) * (2.5/512);
  magnetom[2] = (analogRead(A3) - analogRead(A0)) * (2.5/512);
  
  Serial.print(magnetom[0]);  Serial.print(", ");  Serial.print(magnetom[1]);
  Serial.print(", ");  Serial.print(magnetom[2]);  Serial.print("    ");
  
  
  if(magnetom[0] < magxmin) {
    magxmin = magnetom[0];
  }
  else if(magnetom[0] > magxmax) {
    magxmax = magnetom[0];
  }
  
  if(magnetom[1] < magymin) {
    magymin = magnetom[1];
  }
  else if(magnetom[1] > magymax) {
    magymax = magnetom[1];
  }
  
  if(magnetom[2] < magzmin) {
    magzmin = magnetom[2];
  }
  else if(magnetom[2] > magzmax) {
    magzmax = magnetom[2];
  }
  Serial.print(magxmin);  Serial.print("/");  Serial.print(magxmax);
  Serial.print("    ");
  Serial.print(magymin);  Serial.print("/");  Serial.print(magymax);
  Serial.print("    ");
  Serial.print(magzmin);  Serial.print("/");  Serial.println(magzmax);
  
}




