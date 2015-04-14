void readGeigerString(){
  GeigerString = "";
  if(Serial2.available() > 0){
    
    GeigerString = Serial2.readStringUntil('\n');  
    if(GeigerString != ""){
      Serial.println(GeigerString);
    }
  }
}


