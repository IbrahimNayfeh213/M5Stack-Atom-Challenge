#include "M5Atom.h"
#include "millisDelay.h"
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 27

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(5, 5, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

/*variable declaration*/
String menuMode = "0"; 
int ORNT = 0;
int x    = matrix.width();
int pass = 0;
const uint16_t textWhite = matrix.Color(255,255,255);
uint32_t white = 0xffffff; 
uint32_t red = 0x00ff00;

/*Storing data from sensors*/
float gyroX = 0, gyroY = 0, gyroZ = 0;
float accX = 0, accY = 0, accZ = 0;
float temp = 0;

/*Running average of acceleration values*/
int n_vals = 10;
float accX_avg = ((accX_avg * (n_vals-1))+accX)/n_vals;

///*function to display values onto the Atom*/
//void dispMode(){
//  matrix.fillScreen(0);
//  matrix.setCursor(x, 0);
//  matrix.print(F(menMode));
//  matrix.show();
//  delay(100);
//}

void setup() {
  M5.begin(true,false, true);
  M5.IMU.Init();
  M5.dis.clear();
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(20);
  matrix.setTextColor(textWhite);
}

void loop() {
  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  // get the acceleration data
  // accX = right pointing vector
  // accy = backward pointing vector
  // accZ = upward pointing vector
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  M5.IMU.getTempData(&temp);
  
  if(M5.Btn.wasPressed()){
    M5.dis.fillpix(white);
    delay(500);
    switch (ORNT){
      case 0: // Show Current Temp & Unit
            matrix.fillScreen(0);
            matrix.setCursor(x, 0);
            matrix.print(F("1"));
            matrix.show();
            delay(100);;
          if(M5.Btn.wasPressed()){
            matrix.fillScreen(0);
            matrix.setCursor(x, 0);
            matrix.print(F("TEMP: "));
            matrix.print(temp);
            matrix.print(F(" C"));
            if(--x < -96) {
              x = matrix.width();
            }
          }
          break;
      case 1: // Show Average of past 24H (or less)
            matrix.fillScreen(0);
            matrix.setCursor(x, 0);
            matrix.print(F("2"));
            matrix.show();
            delay(100);;          break;
      case 2: // Color scale & Temp range; Current Color
            matrix.fillScreen(0);
            matrix.setCursor(x, 0);
            matrix.print(F("3"));
            matrix.show();
            delay(100);;          break;
      case 3: // Graph of Temp
            matrix.fillScreen(0);
            matrix.setCursor(x, 0);
            matrix.print(F("4"));
            matrix.show();
            delay(100);;          break;
      case 4: // Change Unit
            matrix.fillScreen(0);
            matrix.setCursor(x, 0);
            matrix.print(F("5"));
            matrix.show();
            delay(100);;          break; 
      default:
          break;
    }
        
   if(abs(accX_avg) > 0.5){ // 0.5g = 45deg tilt angle
      if(accX_avg < -0.5){
        ORNT--;
      }
      if(accX_avg > 0.5){
        ORNT++;
      }
      if (ORNT > 5)
      {
        ORNT = 0;
      }
   }

  }else {
    M5.dis.clear();
  }
  
  M5.update();
}