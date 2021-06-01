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
unsigned long interval2 = 70;
unsigned long loopTime2 = 0; 
millisDelay screenOn;

/*Function that fills the screen with a certain color*/
void fillScreen(uint32_t color){
     M5.dis.fillpix(color);
}

/* checks what unit to display info in */
void checkPress(){
  if(M5.Btn.wasPressed()){
    if(Cels == true){
      Cels = false;
    }else{
      Cels = true;
    }
  }
}

/* changes between Celsius and Fahrenheit */
void changeUnit(){
  if(Cels == true){
    tempUnit = tempVal;
  }else{
    tempUnit = 32 + ((9 * tempVal)/5);
  }
}

//void checkScreenOff() { 
//  if (ScreenOn.justFinished()) { 
//    M5.dis.clear(); // turn leds off
//  }
//}

/* displays the temperature ranges in C and the associated colors */
void colorRangeC(){
  matrix.print(F("< 15"));    //Too cold, blue
  fillScreen(blue);
  while(millis() < loopTime2 + interval2){}
  loopTime2 += interval2;
  M5.dis.clear();             // turn leds off
  matrix.print(F("15 - 30")); //Ideal temp, green
  fillScreen(green);
  while(millis() < loopTime2 + interval2){}
  loopTime2 += interval2;
  M5.dis.clear();
  matrix.print(F("30 - 35")); //A bit hot, yellow
  fillScreen(yellow);
  while(millis() < loopTime2 + interval2){}
  loopTime2 += interval2;
  M5.dis.clear();
  matrix.print(F("> 35"));    //Too hot, red
  fillScreen(red);  while(millis() < loopTime2 + interval2){}
  loopTime2 += interval2;
  M5.dis.clear();
  if(--x < -96) {
    x = matrix.width();
  }
  matrix.show();
}

/* fills screen with a color based on ranges in C */
void currentTempColorC(float curTemp){
  if(curTemp < 15){
    fillScreen(blue);
  }else if (curTemp < 30){
    fillScreen(green);
  }else if (curTemp < 35){
    fillScreen(yellow);
  }else{
    fillScreen(red);
  }
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

void loop() {
  M5.IMU.getTempData(&tempVal);
  checkPress();
  changeUnit();

  colorRangeC();
  currentTempColorC(tempUnit);
  
  while(millis() < loopTime1 + interval1){}
  loopTime1 += interval1;
  M5.update();
}


///* displays the temperature ranges in F and the associated colors */
//void colorRangeF(){
//  matrix.print(F("< 60"));    //Too cold, blue
//  fillScreen(blue);
//  matrix.print(F("60 - 85")); //Ideal temp, green
//  fillScreen(green);
//  matrix.print(F("85 - 95")); //A bit hot, yellow
//  fillScreen(yellow);
//  matrix.print(F("> 95"));    //Too hot, red
//  fillScreen(red);
//  if(--x < -96) {
//    x = matrix.width();
//  }
//  matrix.show();
//}

///* fills screen with a color based on ranges in F */
//void currentTempColorF(float curTemp){
//  if(curTemp < 60){
//    fillScreen(blue);
//  }else if (curTemp < 85){
//    fillScreen(green);
//  }else if (curTemp < 95){
//    fillScreen(yellow);
//  }else{
//    fillScreen(red);
//  }
//}

//  if(Cels == true){
//    colorRangeC();
//  }else{
//    colorRangeF();
//  }  