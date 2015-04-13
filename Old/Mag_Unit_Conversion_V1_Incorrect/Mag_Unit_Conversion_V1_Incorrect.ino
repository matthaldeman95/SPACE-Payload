const int refpin = A0;
const int xpin = A1;
const int ypin = A2;
const int zpin = A3;

int vref;
int xval;
int yval;
int zval;

void setup(){
  Serial.begin(9600);
}

void loop(){
  vref = analogRead(A0);
  xval = analogRead(A1);
  yval = analogRead(A2);
  zval = analogRead(A3);
  float vrefvoltage = vref * (5.0 / 1023.0);
  Serial.print("Vref: ");  Serial.print(vrefvoltage);  
  Serial.print(", Mag Readings (X,Y,Z): ");
  
  float xvoltage = xval * (5.0 / 1023.0);
  float xMag = map(xvoltage,0.5,4.5,-2000,2000);
  Serial.print(xval);  Serial.print(", ");
  
  float yvoltage = yval * (5.0 / 1023.0);
  float yMag = map(yvoltage,0.5,4.5,-2000,2000);
  Serial.print(yval);  Serial.print(", ");
  
  float zvoltage = zval * (5.0 / 1023.0);
  float zMag = map(zvoltage,0.5,4.5,-2000,2000);
  Serial.println(zval);
}




