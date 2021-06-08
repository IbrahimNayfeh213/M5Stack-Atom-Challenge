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
int interval = 3000;

//Set up screen
uint32_t blue = 0x0000ff; // blue color to test
int screenInterval = 1000;
int screenDuration = 0;
bool screenOff = true;

//Displays calming screen
void calmScreen(){
  screenDuration = millis() + screenInterval;
  while(screenDuration > millis()){
    M5.dis.fillpix(blue);
  }
  M5.dis.clear();
}

void fidgetTimer(){
  timeCheck = millis() + interval;
  while(timeCheck > millis()){
    if(abs(accX) > 2 || abs(accY) > 2){
      fidgetState = true;
    }
    if(abs(accX) < 1 &&  abs(accY) < 1){
      fidgetState = false;
      //M5.dis.clear();
    }
    if(fidgetState == true){
      fidgetCtr++;
    }
    if(fidgetState == false){
      fidgetCtr = (0.9 * fidgetCtr);
    }
  }
  if(fidgetCtr > 10){
    M5.dis.fillpix(blue);
  } else {
    fidgetCtr = 0; 
  }
}

void setup() {
    M5.begin(true,false, true);
    M5.IMU.Init(); 
    M5.dis.setBrightness(20);
}

void loop() {
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  timeCheck = millis() + interval;
  while(timeCheck > millis()){
    if(abs(accX) > 2 || abs(accY) > 2){
      fidgetState = true;
    }
    if(abs(accX) < 1 &&  abs(accY) < 1){
      fidgetState = false;
    }
    if(fidgetState == true){
      fidgetCtr++;
    }
    if(fidgetState == false){
      fidgetCtr = (0.99 * fidgetCtr);
    }
  }
  if(fidgetCtr > 4){
    calmScreen();
    fidgetCtr = 1;
  } else {
    fidgetCtr = 1; 
  }
  M5.update();
}

//  if(abs(accX) > 2 || abs(accY) > 2){
//    fidgetState = true;
//    //M5.dis.fillpix(blue);
//  }
//  screenOn();
//  if(abs(accX) < 1 &&  abs(accY) < 1){
//    fidgetState = false;
//    //M5.dis.clear();
//  }