
const int xpin = A1;
const int ypin = A2;
const int zpin = A3;
const int magrefpin = A0;
float magnetom[2];
float xmin; float xmax; float ymin; float ymax; float zmin; float zmax;
float xav; float yav; float zav;
float magavtotal;
float xscale; float yscale; float zscale



//Values found from calibration sketch

#define MAGN_X_MIN ((float) 0.22)
#define MAGN_X_MAX ((float) 0.96)
#define MAGN_Y_MIN ((float) -1.51)
#define MAGN_Y_MAX ((float) 0.23)
#define MAGN_Z_MIN ((float) -1.22)
#define MAGN_Z_MAX ((float) 0.60)

#define MAGN_X_OFFSET ((MAGN_X_MIN + MAGN_X_MAX) / 2.0f)
#define MAGN_Y_OFFSET ((MAGN_Y_MIN + MAGN_Y_MAX) / 2.0f)
#define MAGN_Z_OFFSET ((MAGN_Z_MIN + MAGN_Z_MAX) / 2.0f)

xmax = float(MAGN_X_MAX - MAGN_X_OFFSET);
ymax = float(MAGN_Y_MAX - MAGN_Y_OFFSET);
zmax = float(MAGN_Z_MAX - MAGN_Z_OFFSET);

xmin = MAGN_X_MIN - MAGN_X_OFFSET;
ymin = MAGN_Y_MIN - MAGN_Y_OFFSET;
zmin = MAGN_Z_MIN - MAGN_Z_OFFSET;

mag_av[0] = ((xmax) + (xmin * -1)) / 2.0;
mag_av[1] = ((ymax) + (ymin * -1)) / 2.0;
mag_av[2] = ((zmax) + (zmin * -1)) / 2.0;
magavtotal =  ( mag_av[0] + mag_av[1] + mag_av[2] ) / 3.0;

xscale = (magavtotal / mag_av[0]);
yscale = (magavtotal / mag_av[1]);
zscale = (magavtotal / mag_av[2]);




void setup() {
  Serial.begin(57600);
}

void loop() {
  magnetom[0] = (analogRead(A1) - analogRead(A0)) * (2.5 / 512);
  magnetom[1] = (analogRead(A2) - analogRead(A0)) * (2.5 / 512);
  magnetom[2] = (analogRead(A3) - analogRead(A0)) * (2.5 / 512);

  Serial.print(magnetom[0]);  Serial.print(", ");
  Serial.print(magnetom[1]);  Serial.print(", ");
  Serial.println(magnetom[2]);

  //Apply hard iron calibration values:

  magnetom[0] = (magnetom[0] - MAGN_X_OFFSET);
  magnetom[1] = (magnetom[1] - MAGN_X_OFFSET);
  magnetom[2] = (magnetom[2] - MAGN_X_OFFSET);

  //Apply soft iron calibration values:

  /*
  magnetom[0] = (magnetom[0] * xscale);
  magnetom[1] = (magnetom[1] * yscale);
  magnetom[2] = (magnetom[2] * zscale);
  */

  Serial.print(magnetom[0]);  Serial.print(", ");
  Serial.print(magnetom[1]);  Serial.print(", ");
  Serial.println(magnetom[2]);

}
