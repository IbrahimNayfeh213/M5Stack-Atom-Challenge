#include <Arduino.h>
#include "M5Atom.h"
#include "millisDelay.h"
#include "passive_temp_read.h" //Script for passive temp read
#include "changeTemp.h" //Script for changing the temperature unit
#include "modeCharacters.h" //Script for the non-scrolling numbers for the mode
//
//#include <Adafruit_GFX.h>
//#include <Adafruit_NeoMatrix.h>
//#include <Adafruit_NeoPixel.h>
//
///* Set up text display*/
//#define PIN 27
//
//Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(5, 5, PIN,
//  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
//  NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
//  NEO_GRB            + NEO_KHZ800);

//Set up accel varriables
float accX = 0, accY = 0, accZ = 0;


int tilt_check = 0;   //Define tilt options and orient Matrix
int modeCtr = 1;    //Define counter variables
bool screenOn = false;    //Display on check
int changeMenu = 0; //Confirm tilt direction
bool modeActive = false; //Activate a mode
bool initialOrient = false; //Checks if the Matrix has been oriented properly before tilt

//Define colors
uint32_t white = 0xffffff;
uint32_t red = 0x00ff00;
uint32_t black = 0x0000;
#define cBLACK 0

//Set up wait for change
unsigned long tiltInterval = 750;
float tiltTimer = 0;
bool timeDone = false;

//Activate modes
bool modeOn = false;

void setup() {
  M5.begin(true, false, true);
  M5.IMU.Init();
  matrix.clear();
  Serial.begin(115200);
  Serial.println("Temperature Data");
  
  setupPTRDelay(); //Passive Temp Read, start timer
  setupChangeTemp(); //Initialize temp change
}

void loop() {
  runMenu();
  passiveTempRead();
  checkButton();
  matrix.show();
}

void runMenu(){
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  checkTilt();
  checkScreenOn();
  checkScreenOff();
  if (screenOn == true) {
    checkDelay();
    checkCtr();
    activateMode();
    switch (modeCtr) {
      case 1: //Show active temp
        drawMatrix(one, palette);
        checkMode();
        if(modeOn == true){
          
        }
        checkMode();
        break;
      case 2: //Avg of 24 hours
        drawMatrix(two, palette);
        checkMode();
        if(modeOn == true){
          
        }
        break;
      case 3: //Color scale of temp and current temp color
        drawMatrix(three, palette);
        checkMode();
        if(modeOn == true){
          
        }
        break;
      case 4: //Graph of temp across range
        drawMatrix(four, palette);
        checkMode();
        if(modeOn == true){
          
        }
        break;
      case 5: //Change units
        drawMatrix(five, palette);
        checkMode();
        if(modeOn == true){
          changeTemp();
        }
        checkMode();
        break;
    }
  }
  M5.update();
}

void checkMode(){
  if(M5.Btn.wasPressed() && screenOn == true){
    modeOn = !modeOn;
  }
}

//Checks if the Matrix has been tilted, and in what direction
void checkTilt() {
  if(modeOn == false){
    if (abs(accX) < 0.5 && abs(accY) < 0.5 && accZ > 0.5) {
      tilt_check = 1; //Face down
    } else if (abs(accX) < 0.5 && abs(accY) < 0.5 && accZ < -0.5) {
      tilt_check = 2; //Face up
    } else if (accX < -0.5 && abs(accY) < 0.5 && abs(accZ) < 0.5) {
      tilt_check = 3; //Tilt left
    } else if (accX > 0.5 && abs(accY) < 0.5 && abs(accZ) < 0.5) {
      tilt_check = 4; //Tilt right
    } else {
      tilt_check = 0; //Error
    }
  }
}

//Turns menu on
void checkScreenOn() {
  if (tilt_check == 2){
    if (modeOn == false && M5.Btn.wasPressed()) {
      screenOn = true;
      Serial.println("B");
    }
  }
}

void checkScreenOff() {
  if (tilt_check == 1) {
    screenOn = false;
    matrix.clear();
    modeCtr = 0;
    Serial.println("C");
  }
}

void checkDelay() {
  if (tilt_check == 2) {
    initialOrient = true;
  }
  if (initialOrient == true) {
    while(timeDone == false){
      if (tilt_check == 3 || tilt_check == 4) {
        tiltTimer = millis() + tiltInterval;
        timeDone = true;
        changeMenu = 0;
      } else {
        break;
      }
    }
    if (millis() > tiltTimer && (tilt_check == 3 || tilt_check == 4)) {
      if (tilt_check == 3) {
        changeMenu = 1;
      } else if (tilt_check == 4) {
        changeMenu = 2;
      }
      timeDone = !timeDone;
      initialOrient = false;
    }
  }
}


void checkCtr() {
  if (changeMenu == 0) {
    modeCtr = modeCtr;
  } else {
    if (changeMenu == 1) {
      if (modeCtr == 1) {
        modeCtr = 5;
      } else {
        modeCtr--;
      }
    }
    if (changeMenu == 2) {
      if (modeCtr == 5) {
        modeCtr = 1;
      } else {
        modeCtr++;
      }
    }
  }
  changeMenu = 0;
}

void activateMode() {
  if (screenOn == true) {
    if (M5.Btn.wasPressed()) {
      modeActive = !modeActive;
    }
  }
}

void checkButton(){
  if(M5.Btn.wasPressed()){
    Serial.print("A");
  }
}


//Function that takes a 25 element matrix of image data and prints it on the matrix (for menu numbers) (inspiration: Mike Klepper)
void drawMatrix(int shapeMatrix[], int colors[]) {
  for (int i = 0; i < 25; i++)
    matrix.setPixelColor(i, colors[shapeMatrix[i]]);
}