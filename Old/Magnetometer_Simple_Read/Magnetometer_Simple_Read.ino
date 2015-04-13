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
  Serial.print("Vref voltage: ");
  Serial.print(vrefvoltage);  Serial.print(",     ");
  Serial.print("Mag Values (X,Y,Z): ");
  Serial.print(xval);  Serial.print(", ");
  Serial.print(yval);  Serial.print(", ");
  Serial.println(zval);
}




