#include <BufferedInput.h>
#include <BufferedOutput.h>
#include <loopTimer.h>
#include <millisDelay.h>
#include <SafeString.h>
#include <SafeStringNameSpaceEnd.h>
#include <SafeStringNameSpaceStart.h>
#include <SafeStringReader.h>
#include <SafeStringStream.h>
#include <SerialComs.h>

# include "M5Atom.h"


/*Acceleration variables in the x, y, and z directions*/
float accX, accY, accZ;

/*Time interval for blinks*/
const unsigned long Interval = 1000; 
/*Time passed for intervalDelay function*/
unsigned long previousT = 0; 

/*Colors in hexadecimal*/
uint32_t white = 0xffffff; 
uint32_t red = 0x00ff00; 
uint32_t black = 0x0000; 

/* number of pixels 5x5 */
const int pixel_num = 25; 

/* strobe control */
bool strobeActivate;
int strobeCtr;
long strobeTimer;
millisDelay strobeDelay;

void setup() {
  M5.begin(true,false, true); 
  fillScreen(black);
  M5.IMU.Init();
  strobeCtr = 0;
  strobeTimer = 0;
}

/*Function that fills the screen with a certain color*/
void fillScreen(uint32_t color){
  for(int i = 0 ; i < pixel_num; i++)
     M5.dis.drawpix(i,color);
    
}

uint8_t FSM = 0;

/*Time Delay function */
void intervalDelay(uint32_t colors){  
  unsigned long currentT = millis();
  if(currentT - previousT >= Interval){ // if time from start reached 1000 mili seconds the screen will be filled with black 
     fillScreen(colors);
     previousT = currentT; // updates time for the next loop
  }
}

uint32_t currentColor = black; 

void loop() {
//  M5.IMU.getAccelData(&accX, &accY, &accZ);
    fillScreen(red);
  while(strobeActivate = true){
      for(int i = 60; i >= 0; i--)
    {
      M5.dis.setBrightness(i);
    }
  
    for (int i = 0; i < 60; i++)
    {
      M5.dis.setBrightness(i);
    }
  }
  M5.update();
}

// possibly for acceleration
//void setup() {
//  oldX = -1;
//  oldY = -1;
//}
//
//void loop() {
//  float accX, accY, accZ;
//  int x, y;
//
//  M5.IMU.getAccelData(&accX, &accY, &accZ);
//  x = constrain(accX * 5 + 2, 0, 4);
//  y = constrain(accY * 5 + 2, 0, 4);
//  if (oldX != x || oldY != y) {
//    M5.dis.drawpix(oldX, oldY, 0x000000);
//    M5.dis.drawpix(x, y, 0xffffff);
//    oldX = x;
//    oldY = y;
//  }
//}
//

//test
//Function to change brightness of the LEDs
//void setBrightness(uint8_t brightness)
//  brightness=20;
