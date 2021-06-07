#include <Arduino.h>
#include "M5Atom.h"
#include "millisDelay.h"
#include "characters.c" //From tilt game
//bool IMU_ready = false;

//Set up accel varriables 
float accX = 0, accY = 0, accZ = 0;

//Define tilt options and orient Matrix
int tilt_check = 0;

//Define counter variables 
int modeCtr = 1;

//Display on check
bool screenOn = false;

//Confirm tilt direction
int changeMenu = 0;

//Define colors
uint32_t white = 0xffffff; 
uint32_t red = 0x00ff00; 
uint32_t black = 0x0000; 
#define cBLACK 0

//Set up wait for change
unsigned long interval = 500; 
millisDelay waitDelay;

//Display numbers of modes
void display_number(uint8_t number){
  if(number < 20){
    M5.dis.displaybuff((uint8_t *)image_numbers[number]);
  } else {
    M5.dis.displaybuff((uint8_t *)image_dot);
  }
}

//Checks if the Matrix has been tilted, and in what direction
void checkTilt(){
  if(abs(accX) < 0.5 && abs(accY) < 0.5 && accZ > 0.5){
    tilt_check = 1; //Face down
  } else if (abs(accX) < 0.5 && abs(accY) < 0.5 && accZ < -0.5){
    tilt_check = 2; //Face up
  } else if (accX < -0.5 && abs(accY) < 0.5 && abs(accZ) < 0.5){
    tilt_check = 3; //Tilt left
  } else if (accX > 0.5 && abs(accY) < 0.5 && abs(accZ) < 0.5){
    tilt_check = 4; //Tilt right
  } else{
    tilt_check = 0; //Error
  }
}

//Turns menu on
void checkScreenOn(){
  if(tilt_check == 2 && M5.Btn.wasPressed()){
    screenOn = true;
    modeCtr = 1;
  }
}

void checkScreenOff(){
  if(tilt_check == 1){
    screenOn = false;
    M5.dis.clear();
    modeCtr = 0;
  }
}

void checkDelay(){
  if(screenOn = true && (tilt_check == 3 || tilt_check == 4)){
    waitDelay.start(interval);
    if(waitDelay.justFinished()){ 
      if(tilt_check = 3){
        changeMenu = 1;
      } else if(tilt_check = 4){
        changeMenu = 2;
      }
    }
  }
}

void checkCtr(){
  if(changeMenu == 1){
    modeCtr--;
  }
  if(changeMenu == 2){
    modeCtr++;
  }
}

void setup() {
  M5.begin(true, false, true);
  M5.IMU.Init();
  M5.dis.clear();
}

void loop() {
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  checkTilt();
  checkScreenOn();
  checkScreenOff();
  checkDelay();
  checkCtr();
  switch (modeCtr){
    case 1: //Show active temp
      display_number(modeCtr);
      break;
    case 2: //Avg of 24 hours
      display_number(modeCtr);
      break;
    case 3: //Color scale of temp and current temp color
      display_number(modeCtr);
      break;
    case 4: //Graph of temp across range
      display_number(modeCtr);
      break;
    case 5: //Change units 
      display_number(modeCtr);
      break;
  }
  M5.update();
}