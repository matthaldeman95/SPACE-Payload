

#include <math.h>

const int xpin = A1;
const int ypin = A3;
const int zpin = A0;
const int magrefpin = A2;

float magnetom[2];
float magnitude; 

double angle;
double heading;

#define MAGN_X_MIN ((float) -0.11)
#define MAGN_X_MAX ((float) 0.45)
#define MAGN_Y_MIN ((float) -0.94)
#define MAGN_Y_MAX ((float) 0.29)
#define MAGN_Z_MIN ((float) -0.81)
#define MAGN_Z_MAX ((float) 0.47)

#define MAGN_X_OFFSET ((MAGN_X_MIN + MAGN_X_MAX) / 2.0)
#define MAGN_Y_OFFSET ((MAGN_Y_MIN + MAGN_Y_MAX) / 2.0)
#define MAGN_Z_OFFSET ((MAGN_Z_MIN + MAGN_Z_MAX) / 2.0)

float xmax = float(MAGN_X_MAX - MAGN_X_OFFSET);
float ymax = float(MAGN_Y_MAX - MAGN_Y_OFFSET);
float zmax = float(MAGN_Z_MAX - MAGN_Z_OFFSET);

float xmin = float(MAGN_X_MIN - MAGN_X_OFFSET);
float ymin = float(MAGN_Y_MIN - MAGN_Y_OFFSET);
float zmin = float(MAGN_Z_MIN - MAGN_Z_OFFSET);

float xav = ((xmax) + (xmin * -1)) / 2.0;
float yav = ((ymax) + (ymin * -1)) / 2.0;
float zav = ((zmax) + (zmin * -1)) / 2.0;

float avg = (xav + yav + zav) / 3.0;

float xscale = (avg / xav);
float yscale = (avg / yav);
float zscale = (avg / zav);

void setup() {
  Serial.begin(57600);
}

void loop() {
  delay(100);
  
  magnetom[0] = (analogRead(xpin) - analogRead(magrefpin)) * (2.5 / 512);
  magnetom[1] = (analogRead(ypin) - analogRead(magrefpin)) * (2.5 / 512);
  magnetom[2] = (analogRead(zpin) - analogRead(magrefpin)) * (2.5 / 512);
  
  magnetom[0] = (magnetom[0] - MAGN_X_OFFSET);
  magnetom[1] = (magnetom[1] - MAGN_Y_OFFSET);
  magnetom[2] = (magnetom[2] - MAGN_Z_OFFSET);
  
  magnetom[0] *= xscale;
  magnetom[1] *= yscale;
  magnetom[2] *= zscale;
  
  magnitude = sqrt(magnetom[0]*magnetom[0] + magnetom[1]*magnetom[1] + magnetom[2]*magnetom[2]);
  
  
  
  Serial.print(magnetom[0]);  Serial.print(", ");
  Serial.print(magnetom[1]);  Serial.print(", ");
  Serial.print(magnetom[2]);  Serial.print("       ");
  Serial.print(magnitude);  Serial.print("       ");
  
  angle = (magnetom[0]) / (magnetom[1]);
  angle = (atan(angle)) * (180/PI);
  
  if(magnetom[1] > 0){
    heading = 90 - angle;
  }
  else if(magnetom[1] < 0){
    heading = 270 - angle;
  }
  else if(magnetom[1] = 0){
    if(magnetom[0] < 0){
      heading = 180;
    }
    else if(magnetom[0] > 0){
      heading = 0.0;
    }
  }
  
  Serial.println(heading);
  
 
}
