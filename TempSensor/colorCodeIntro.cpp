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

/* variable declaration*/
/* temp vars*/
bool Cels = true;
float tempVal = 0;
float tempUnit = 0;

/* text vars*/
const uint16_t textWhite = matrix.Color(255, 255, 255);
int x    = matrix.width();
int pass = 0;

/* screen color values */
uint32_t blue = 0x0000ff;
uint32_t green = 0x00ff00;
uint32_t yellow = 0xffff00;
uint32_t red = 0x00ff00;

/* delay settings */
unsigned long interval1 = 80;
unsigned long loopTime1 = 0; 
unsigned long interval2 = 100;
unsigned long loopTime2 = 0; 

/*Function that fills the screen with a certain color*/
void fillScreen(uint32_t color){
     M5.dis.fillpix(color);
}

void setup() {
  M5.begin(true,false, true);
  M5.dis.clear();
  M5.dis.setBrightness(20);
  M5.IMU.Init();
  
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(20);
  matrix.setTextColor(textWhite);
}

void printText(char Strng[10] = "range"){
  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  matrix.print(F(Strng));
  if(--x < -100) {
    x = matrix.width();
  }
  while(millis() < loopTime2 + interval2){}
  loopTime2 += interval2;
  matrix.show();
}
void loop() {
  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  printText("< 15");    //Too cold, blue
//  fillScreen(blue);
//  while(millis() < loopTime2 + interval2){}
//  loopTime2 += interval2;
//  M5.dis.clear();             // turn leds off
  printText("15 - 30 "); //Ideal temp, green
//  fillScreen(green);
//  while(millis() < loopTime2 + interval2){}
//  loopTime2 += interval2;
//  M5.dis.clear();
  printText("30 - 35 "); //A bit hot, yellow
//  fillScreen(yellow);
//  while(millis() < loopTime2 + interval2){}
//  loopTime2 += interval2;
//  M5.dis.clear();
  printText("> 35 ");    //Too hot, red
//  fillScreen(red);  
//  while(millis() < loopTime2 + interval2){}
//  loopTime2 += interval2;
//  M5.dis.clear();
}

  