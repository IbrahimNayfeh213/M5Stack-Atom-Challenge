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

//Screen color values
uint32_t black = 0x0000; 
uint32_t blue1 = 0x0000ff; // blue color to test
uint32_t L1color = 0xD1EEEE;  // light cyan2
uint32_t L2color = 0xADEAEA;  // turquoise
uint32_t L3color = 0x70DBDB;  // medium turquoise
uint32_t L4color = 0x00CED1;  // dark turquoise (SVG)
uint32_t L5color = 0x00868B;  // turquoise4

//Spiral display timer
millisDelay Delay; 
int Screeninterval = 900;
int i = 0; // counter


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

//Displays calming screen
void calmScreen(){
  Delay.start(Screeninterval);
  i++;
  while(i > 0){
  displaySpiral();
  }
}

//Determines if the wearer is fidgetting or just moving naturally
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

void displaySpiral(){
    switch (i){
      case 0:
        M5.dis.clear();
        break;
      case 1:
        M5.dis.fillpix(L5color);
        CheckDelay();
        break;
      case 2:
        M5.dis.clear();
        CheckDelay();
        break;
      case 3:
        M5.dis.fillpix(L5color);
        CheckDelay();
        break;
      case 4: 
        M5.dis.drawpix(12,L1color); // sets the center pixel to the color we choose
        CheckDelay(); // calls function to check the delay
        break;
      case 5: //Inner diamond
        M5.dis.drawpix(7,L2color);
        M5.dis.drawpix(11,L2color);
        M5.dis.drawpix(13,L2color);
        M5.dis.drawpix(17,L2color);
        CheckDelay();
        break;
      case 6:
        M5.dis.drawpix(2,L3color);
        M5.dis.drawpix(6,L3color);
        M5.dis.drawpix(8,L3color);
        M5.dis.drawpix(10,L3color);
        M5.dis.drawpix(14,L3color);
        M5.dis.drawpix(16,L3color);
        M5.dis.drawpix(18,L3color);
        M5.dis.drawpix(22,L3color);
        CheckDelay();
        break;
      case 7: 
        M5.dis.drawpix(1,L4color);
        M5.dis.drawpix(5,L4color);
        M5.dis.drawpix(3,L4color);
        M5.dis.drawpix(9,L4color);
        M5.dis.drawpix(15,L4color);
        M5.dis.drawpix(19,L4color);
        M5.dis.drawpix(21,L4color);
        M5.dis.drawpix(23,L4color);
        CheckDelay();
        break;
      case 8: 
        M5.dis.drawpix(0,L5color);
        M5.dis.drawpix(4,L5color);
        M5.dis.drawpix(20,L5color);
        M5.dis.drawpix(24,L5color);
        CheckDelay();
        break;
      case 9:
        M5.dis.drawpix(0,L5color);
        M5.dis.drawpix(1,L5color);
        M5.dis.drawpix(2,L5color);
        M5.dis.drawpix(3,L5color);
        M5.dis.drawpix(4,L5color);
        M5.dis.drawpix(5,L5color);
        M5.dis.drawpix(9,L5color);
        M5.dis.drawpix(10,L5color);
        M5.dis.drawpix(14,L5color);
        M5.dis.drawpix(15,L5color);
        M5.dis.drawpix(19,L5color);
        M5.dis.drawpix(20,L5color);
        M5.dis.drawpix(21,L5color);
        M5.dis.drawpix(22,L5color);
        M5.dis.drawpix(23,L5color);
        M5.dis.drawpix(24,L5color);
        M5.dis.drawpix(6,L3color);
        M5.dis.drawpix(7,L3color);
        M5.dis.drawpix(8,L3color);
        M5.dis.drawpix(11,L3color);
        M5.dis.drawpix(13,L3color);
        M5.dis.drawpix(16,L3color);
        M5.dis.drawpix(17,L3color);
        M5.dis.drawpix(18,L3color);
        M5.dis.drawpix(12,L1color);
        CheckDelay();
        break;
      case 10:
        M5.dis.clear();
        CheckDelay();
        break;  
      case 11:
        M5.dis.drawpix(0,L5color);
        M5.dis.drawpix(1,L5color);
        M5.dis.drawpix(2,L5color);
        M5.dis.drawpix(3,L5color);
        M5.dis.drawpix(4,L5color);
        M5.dis.drawpix(5,L5color);
        M5.dis.drawpix(9,L5color);
        M5.dis.drawpix(10,L5color);
        M5.dis.drawpix(14,L5color);
        M5.dis.drawpix(15,L5color);
        M5.dis.drawpix(19,L5color);
        M5.dis.drawpix(20,L5color);
        M5.dis.drawpix(21,L5color);
        M5.dis.drawpix(22,L5color);
        M5.dis.drawpix(23,L5color);
        M5.dis.drawpix(24,L5color);
        M5.dis.drawpix(6,L3color);
        M5.dis.drawpix(7,L3color);
        M5.dis.drawpix(8,L3color);
        M5.dis.drawpix(11,L3color);
        M5.dis.drawpix(13,L3color);
        M5.dis.drawpix(16,L3color);
        M5.dis.drawpix(17,L3color);
        M5.dis.drawpix(18,L3color);
        M5.dis.drawpix(12,L1color);
        CheckDelay();
        break;
      case 12:
        M5.dis.drawpix(0,L5color);
        M5.dis.drawpix(1,L5color);
        M5.dis.drawpix(2,L5color);
        M5.dis.drawpix(3,L5color);
        M5.dis.drawpix(4,L5color);
        M5.dis.drawpix(5,L5color);
        M5.dis.drawpix(9,L5color);
        M5.dis.drawpix(10,L5color);
        M5.dis.drawpix(14,L5color);
        M5.dis.drawpix(15,L5color);
        M5.dis.drawpix(19,L5color);
        M5.dis.drawpix(20,L5color);
        M5.dis.drawpix(21,L5color);
        M5.dis.drawpix(22,L5color);
        M5.dis.drawpix(23,L5color);
        M5.dis.drawpix(24,L5color);
        CheckDelay();
        break;
      case 13:
        M5.dis.drawpix(6,L3color);
        M5.dis.drawpix(7,L3color);
        M5.dis.drawpix(8,L3color);
        M5.dis.drawpix(11,L3color);
        M5.dis.drawpix(13,L3color);
        M5.dis.drawpix(16,L3color);
        M5.dis.drawpix(17,L3color);
        M5.dis.drawpix(18,L3color);
        CheckDelay();
        break;
      case 14: 
        M5.dis.drawpix(12,L1color);
        CheckDelay();
        break;
      case 15:
        M5.dis.clear();
        CheckDelay();
        break;   
      default:
        break;
    }
    
    if(i == 16) 
      i = 0; // resets counter
}

void CheckDelay(){ // functions that checks if delay ended and sets screen to black
  if(Delay.justFinished())
  {
    Delay.repeat();
    M5.dis.fillpix(black);
    i++; // increments counter
  } 
}