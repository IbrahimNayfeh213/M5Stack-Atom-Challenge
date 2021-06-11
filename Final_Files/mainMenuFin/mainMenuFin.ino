/*
 * By: Bayan Assali, Ibrahim Nayfeh, and Gelila Kebede
 * Date: 11 June 2021
 * 
 * Temperature sensor that passively reads temperature, and engages in 5 different modes
 * 
 * 
 * Refernces:
 * Mike Klepper 
 * Patrio Geek blog
 *  ATOM Matrix: Using the MPU6886 Accelerometer - 
 *    Reading and Displaying Values, aka MPU68866.ino
 *    Showing Device Orientation, aka AccelerometerTest02.ino
 *  ATOM Matrix: Basic Display Usage
 *  ATOM Matrix: Advanced Display Usage - 
 *    Scrolling Text Messages, aka Text-Display-01.ino
 *  
 * Github Repositories:
 *  m5stack/M5Atom
 *    https://github.com/m5stack/M5Atom
 *  electricidea/M5ATOM/Tilt-Game
 *    https://github.com/electricidea/M5ATOM/tree/master/Tilt-Game
 *    By Hans-Günther Nusseck (electricidea)
 *    
 * Adafruit Arduino Library Use
 *  https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-use
 */

#include <Arduino.h>
#include "M5Atom.h"
#include "millisDelay.h"
#include "functionIndex.h" //Script for changing the temperature unit
#include "modeCharacters.h" //Script for the non-scrolling numbers for the mode

//Set up accel varriables
float accX = 0, accY = 0, accZ = 0;

//Set up tilt values
int tilt_check = 0;         //Define tilt options and orient Matrix
int modeCtr = 1;            //Define counter variables
bool screenOn = false;      //Display on check
int changeMenu = 0;         //Confirm tilt direction
bool menuActive = false;    //Activate a mode
bool initialOrient = false; //Checks if the Matrix has been oriented properly before tilt

//Define colors
uint32_t white = 0xffffff;
uint32_t black = 0x000000;


//Set up wait for change
unsigned long tiltInterval = 750;
float tiltTimer = 0;
bool timeDone = false;

//Activate modes
bool modeOn = false;

//Temp variables
float initalTempValue = 0;
float convertTemp = 0;

void setup() {
  //Set up Matrix
  M5.begin(true, false, true);
  M5.IMU.Init();
  matrix.clear();
  Serial.begin(115200);
  Serial.println("Temperature Data");

  //Set up functions
  setupPTRDelay(); //Passive Temp Read, start timer
  setupMatrix(); //Initialize matrix
  setupGraph(); //Graph, start timer
}

void loop() {
  runMenu();
  passiveTempRead();
  matrix.show();
}

void runMenu(){
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  M5.IMU.getTempData(&initalTempValue);
  checkTilt();
  checkScreenOn();
  if (screenOn == true) {
    checkDelay();
    checkCtr();
    convertTemp = changeUnit(initalTempValue);
    activateMenu();
    //  modeOn = true;
    switch (modeCtr) {
      case 1: //Show active temp
        drawMatrix(one, palette);
        checkMode();
        if(modeOn == true){
          printCurrentTemp(modeOn, convertTemp);
        }
        checkMode();
        break;
      case 2: //Avg of 24 hours
        drawMatrix(two, palette);
        checkMode();
        if(modeOn == true){
          printDayAvg(convertTemp);
        }
        checkMode();
        break;
      case 3: //Color scale of temp and current temp color
        drawMatrix(three, palette);
        checkMode();
        if(modeOn == true){
          displayColorCodedTemp();
        }
        checkMode();
        break;
      case 4: //Graph of temp across range
        drawMatrix(four, palette);
        checkMode();
        if(modeOn == true){
          graphLoop();
        }
        checkMode();
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

//Activated the menu function
void activateMenu() {
  if (screenOn == true) {
    if (M5.Btn.wasPressed()) {
      menuActive = true;
      modeOn = false;
      Serial.println("A");
    }
  }
}

//Checks if button had been pressed to start/stop various modes
void checkMode(){
  if(screenOn == true){
    if(menuActive == true){
      if(M5.Btn.wasPressed()){
        if(modeOn == true){
          modeOn = false;
          Serial.println("B");
        } else {
          modeOn = true;
          Serial.println("C");
        }
      }
    }
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
      Serial.println("D");
    }
  } else if (tilt_check == 1) {
    screenOn = false;
    matrix.clear();
    modeCtr = 0;
    menuActive = false;
    modeOn = false;
    Serial.println("E");
  }
}

//Creats delay to differentiate between movement and tilts
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

//Switches between modes
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

//Function that takes a 25 element matrix of image data and prints it on the matrix (for menu numbers) (inspiration: Mike Klepper)
void drawMatrix(int shapeMatrix[], int colors[]) {
  for (int i = 0; i < 25; i++)
    matrix.setPixelColor(i, colors[shapeMatrix[i]]);
}
