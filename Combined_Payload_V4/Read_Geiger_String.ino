void readGeiger(){
  boolean stringcomplete = false;
  GeigerString = "";
    Serial2.begin(9600);

       GeigerString = Serial2.readStringUntil('\n');
       Serial.println(GeigerString);
     
     Serial2.end();
}

