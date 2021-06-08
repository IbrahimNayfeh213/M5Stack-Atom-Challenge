#include <Arduino.h>
#include "M5Atom.h"
#include "millisDelay.h"

//Set up accel varriables 
float accX = 0, accY = 0, accZ = 0;

//Set up fidget checks
bool fidgetState = false;
int fidgetCtr = 0;

//Set up time varriables
int timeCheck = 0;
int interval = 500;

//Set up screen
uint32_t blue = 0x0000ff; // blue color to test
millisDelay screenDelay; 
int screenInterval = 1000;

void setup() {
    M5.begin(true,false, true); 
    M5.dis.setBrightness(20);
}

void loop() {
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  if(abs(accX) > 3 || abs(accY) > 3){
  fidgetState = true;
    M5.dis.fillpix(blue);
  }
//  if(abs(accX) < 1 || abs(accY) < 1 || abs(accZ) < 1){
//    fidgetState = false;
//  }
//  if(millis() > timeCheck && fidgetState == true){
//    fidgetCtr++;
//  }
//  if(fidgetCtr > 1){
//    M5.dis.fillpix(blue);
//    screenDelay.start(screenInterval);
//    if(screenDelay.justFinished()){
//      M5.dis.clear();
//      fidgetCtr = 0;
//    }
//  }
}