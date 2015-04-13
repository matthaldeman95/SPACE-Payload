int xpin = A0;
int ypin = A1;
int vref = A2;

void setup() {
  Serial.begin(57600);
}

void loop() {
  float xval = (analogRead(xpin)-analogRead(vref))*(2.5/512);
  float yval = (analogRead(ypin)-analogRead(vref))*(2.5/512);
  Serial.print(xval);  Serial.print(", ");  Serial.println(yval);
  
}
