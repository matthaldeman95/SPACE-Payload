String GeigerString;

void setup() {
  Serial.begin(57600);
}

void loop() {
  readGeiger(); 
  count();
  
  
}


