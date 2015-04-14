String GeigerString;

void setup() {
  Serial2.begin(9600);
  Serial.begin(9600);
}

void loop() {
  readGeiger();  
  
}


