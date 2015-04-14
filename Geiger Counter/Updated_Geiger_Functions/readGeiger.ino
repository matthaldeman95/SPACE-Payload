String readGeiger(){
  boolean stringcomplete = false;
   GeigerString = "";
  if(Serial2.available() > 0){
     if(stringcomplete == false){
        if(Serial2.peek() == '\n'){
        Serial2.read();
        stringcomplete = true;
      }
      
      else {
        GeigerString = Serial2.readStringUntil('\n');
          if(GeigerString != ""){
            Serial.println(GeigerString);
          }
      }
     }
  }
}
