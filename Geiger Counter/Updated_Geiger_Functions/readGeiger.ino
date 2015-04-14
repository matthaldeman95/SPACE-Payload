void readGeiger(){
  boolean stringcomplete = false;
  GeigerString = "";
    Serial2.begin(9600);

       GeigerString = Serial2.readStringUntil('\n');
       Serial.println(GeigerString);
     
     Serial2.end();
}


void count(){
  delay(1000);
  Serial.println(1);
  delay(1000);
  Serial.println(2);
  delay(1000);
  Serial.println(3);
  delay(1000);
  Serial.println(4);
  delay(1000);
  Serial.println(5);
}
