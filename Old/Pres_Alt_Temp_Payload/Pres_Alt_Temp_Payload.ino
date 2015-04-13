#include <LiquidCrystal.h>

#include <MPL3115A2.h>

#include <Wire.h>

MPL3115A2 myPressure;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

float altitude;
float maxAlt = 0;
float currentTime;

void setup(){
  Wire.begin();
  Serial.begin(9600);
  lcd.begin(16,2);
  
  myPressure.begin();
  myPressure.setModeAltimeter();
  
  myPressure.setOversampleRate(7);
  myPressure.enableEventFlags();
}

void loop(){
  
  delay(500);
  
  altitude = myPressure.readAltitudeFt();
  
  currentTime = millis();
  
  Serial.print("Current time: ");
  Serial.print(currentTime);
  Serial.print(", Altitude(ft): ");
  Serial.print(altitude, 2);
  
  float temperature = myPressure.readTempF();
  Serial.print(", Temp(f): ");
  Serial.println(temperature, 2);
  
  lcd.setCursor(0,0);
  lcd.print("Alt (ft): ");
  lcd.setCursor(10,0);
  lcd.print(altitude);
  
  if(altitude > maxAlt && currentTime > 5000){
    maxAlt = altitude;
    lcd.setCursor(0,1);
    lcd.print("Max: ");
    lcd.setCursor(8,1);
    lcd.print(maxAlt);
    Serial.print(", Max Alt (ft): ");
    Serial.println(maxAlt);
  }
}
  
  


