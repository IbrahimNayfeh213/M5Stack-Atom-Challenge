#include "M5Atom.h"
#include "millisDelay.h"

/*variable declaration*/
float temp_value;
int recordData[20];
char numbToString[10]:

void setup() {
  M5.begin(true,false, true);
  M5.IMU.Init();
  M5.dis.clear();
  Serial.begin(9600);
}

void loop() {
  M5.IMU.getTempData(&temp_value);
  Serial.print(temp_value);
  Serial.print(":");
}