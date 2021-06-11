/*
 * Holds all the necessay functions to run the temeprature sensor
 */

#include "M5Atom.h"
#include "millisDelay.h"
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

/* Set up text display*/
#define PIN 27

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(5, 5, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

/* Text variables */
/* text vars */
const uint16_t textWhite = matrix.Color(255, 255, 255);
int x    = matrix.width();
int pass = 0;

/* Screen color variables */
/* screen color values */
uint32_t blue = 0x0000ff;
uint32_t green = 0x00ff00;
uint32_t yellow = 0xffff00;
uint32_t orange = 0xffa500;
uint32_t red = 0xff0000;

/* Setup functions */
void setupMatrix() { 
  matrix.begin();
  matrix.clear();
  matrix.setTextWrap(false);
  matrix.setBrightness(20);
  matrix.setTextColor(textWhite);
}

/* Changing Unit */
/* variable declaration */
/* temp vars */
bool Cels = true;

/* delay settings */
unsigned long unitInterval = 60;
unsigned long loopTime = 0; 

/* Set up accel varriables */
float accCTX = 0, accCTY = 0, accCTZ = 0;
bool switchUnit = false;
bool timeCT = false;
unsigned long tiltCTTimer = 0;
unsigned long tiltCTInterval = 500;

/* Get accel data */
void changeTempTilt() {
  M5.IMU.getAccelData(&accCTX, &accCTY, &accCTZ);
  if (abs(accCTX) > 0.5 && abs(accCTY) < 0.5 && abs(accCTZ) < 0.5) {
    switchUnit = true;
  } else {
    switchUnit = false;
  }
  M5.update();
}

void changeDelay() {
  if (switchUnit == true) {
    while(timeCT == false){
      tiltCTTimer = millis() + tiltCTInterval;
      timeCT = true;
    }
    if (millis() < tiltCTTimer && switchUnit == false) {
      timeCT = !timeCT;
      switchUnit = false;
    }
    if (millis() > tiltCTTimer && switchUnit == true) {
      Cels = !Cels;
      timeCT = !timeCT;
      switchUnit = false;
    }
  }
}

void checkUnit(){
  if(M5.Btn.wasPressed()){
    if(Cels == true){
      Cels = false;
    }else{
      Cels = true;
    }
  }
  M5.update();
}

void changeTemp() {
  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  changeTempTilt();
  changeDelay();
  if(Cels == false){
    matrix.print(F("FAHR"));
  }
  if(Cels == true){
    matrix.print(F("CELS")); 
  }
  if(--x < -96) {
    x = matrix.width();
  }
  matrix.show();
  while(millis() < loopTime + unitInterval){}
  loopTime += unitInterval;
  M5.update();
}

float changeUnit(float inTemp){
  float outTemp;
  if(Cels == true){
    outTemp = inTemp;
  } else {
    outTemp = 32 + ((9 * inTemp) / 5);
  }
  return(outTemp);
}

/* Passive Temp Read */
/* Variables */
millisDelay ReadDelay;
int intervalTDA = 60000;

void setupPTRDelay(){
  ReadDelay.start(intervalTDA);
}


/* Display Current Temp */
/* Variables */
unsigned long intervalDCT = 100;
unsigned long delayDCT = 0;
bool timerOnDCT = false; 

/* Functions */
void printCurrentTemp(bool screen, float temp) {
  if(screen == true){
    if(M5.Btn.wasPressed()){
      matrix.fillScreen(0);
      //delayDCT = millis() + intervalDCT;
      timerOnDCT = true;
    }
    matrix.fillScreen(0);
    matrix.setCursor(x, 0);
    matrix.print(F("TEMP: "));
    matrix.print(temp);
    if(Cels == true){
      matrix.print(F("C"));
    } else {
      matrix.print(F("F"));
    }
    if(--x < -96) {
      x = matrix.width();
    }
    matrix.show();
    while(millis() < delayDCT + intervalDCT){}
    delayDCT += intervalDCT;
    M5.update();
  }
}

/* Display Average Temp */
/* Variables */
float tempValInitial;
float tempValUnit;
float minVal[1440];
int minCtr = 0;
int minSince = 0;
int minTotal = 0;
int minAvg = 0;
unsigned long intervalDelayTDA = 100;
unsigned long delayTDA = 0;

/* Functions */
void passiveTempRead(){
  if(ReadDelay.justFinished()){
    ReadDelay.repeat();
    M5.IMU.getTempData(&tempValInitial);
    minVal[minCtr] = tempValInitial;
    Serial.print(minVal[minCtr], 2);
    Serial.print(", ");
    minCtr++;
    minSince++;
  }
  if(minCtr < 1440){
    minTotal += minVal[minCtr];
    minAvg = minTotal / (minCtr + 1);
  } else {
    minCtr = minSince % 1440; 
    if(minCtr == 0){
      
    } else {
      for(int i = 0; i < 1440; i++){
        minTotal += minVal[i];
      }
      minAvg = minTotal / 1440;
    }
  }
}

void printDayAvg (float inTemp){
  matrix.clear();
  matrix.setCursor(x, 0);
  matrix.print(F("DAY AVG TEMP: "));
  
  matrix.print(inTemp);
  if(Cels == true){
    matrix.print(F("C"));
  } else {
    matrix.print(F("F"));
  }
  if(--x < -96) {
    x = matrix.width();
  }
  matrix.show();
  while(millis() < delayTDA + intervalDelayTDA){}
  delayTDA += intervalDelayTDA;
  M5.update();
}
/* Colored Temp Display */
/* Variables */
/* screen color values */
uint32_t crntColor;

/* temp vars*/
float tempValCC = 0;
float tempUnitCC = 0;

/* Functions */
/*Function that fills the screen with a certain color*/
float changeUnitCC(float intTemp){
  float outTemp;
  if(Cels == true){
    outTemp = intTemp;
  }else{
    outTemp = 32 + ((9 * intTemp)/5);
  }
  return(outTemp);
}

void displayTempColor(uint32_t color){
     matrix.setPixelColor(0, blue);
     matrix.setPixelColor(1, green);
     matrix.setPixelColor(2, yellow);
     matrix.setPixelColor(3, orange);
     matrix.setPixelColor(4, red);
     matrix.fill(color, 5, 20);
}

/* fills screen with a color based on ranges in C */
uint32_t currentTempColorC(float curTemp){
  uint32_t tColor;
  if(curTemp < 15){
    tColor = blue;
  } else if (curTemp < 30){
    tColor = green;
  } else if (curTemp < 35){
    tColor = yellow;
  } else if (curTemp < 40){
    tColor = orange;
  } else if (curTemp < 45){
    tColor = red;
  } else {}
  return(tColor);
}

void displayColorCodedTemp() {
  M5.IMU.getTempData(&tempValCC);
  tempUnitCC = changeUnitCC(tempValCC);
  crntColor = currentTempColorC(tempUnitCC);
  displayTempColor(crntColor);
  matrix.show();
  M5.update();
}

/* Color coded graph */
/* Variables */
uint32_t curColor;
int hourSince = 0;

millisDelay graphDelay;
int gInterval = 60000;

float hourVal[24];
int minSum = 0;

/* Functions */
int minToHour(){
  int hCtr = 0;
  int hourCount = minSince / 60;
  while(hCtr < hourCount){
    int mCtr = hCtr * 60;
    int mEnd = mCtr + 60;
    while(mCtr < mEnd){
      minSum += minVal[mCtr];
      mCtr++;
    }
    hourVal[hCtr] = minSum / 60;
    hCtr++;
    minSum = 0;
  }
  return(hourCount);
}

uint32_t tempColorSelect(float tempVal){
  uint32_t color;
  if(tempVal < 15){
    color = blue;
  }else if (tempVal < 30){
    color = green;
  }else if (tempVal < 35){
    color = yellow;
  }else{
    color = red;
  }
  return(color);
}

void colorPixel(int pixel,uint32_t color){
   matrix.setPixelColor(pixel, color);
}

void displayGraph(int hourCount){
  for(int gCtr = 0; gCtr < hourCount; gCtr++){
    curColor = tempColorSelect(hourVal[gCtr]);
    colorPixel(gCtr, curColor);
  }
}

void setupGraph(){
  graphDelay.start(gInterval);
}

void graphLoop() {
  matrix.clear();
  hourSince = minToHour();  
  displayGraph(hourSince);
  matrix.show();
  M5.update();  
}
