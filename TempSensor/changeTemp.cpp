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

/* variable declaration */
/* temp vars */
bool Cels = true;

/* text vars */
const uint16_t textWhite = matrix.Color(255, 255, 255);
int x    = matrix.width();
int pass = 0;

/* delay settings */
unsigned long interval = 60;
unsigned long loopTime = 0; 

void checkUnit(){
  if(M5.Btn.wasPressed()){
    if(Cels == true){
      Cels = false;
    }else{
      Cels = true;
    }
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
  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  checkUnit();
  if(Cels == true){
    matrix.print(F("FAHR"));
  }
  if(Cels == false){
    matrix.print(F("CELS")); 
  }
  if(--x < -96) {
    x = matrix.width();
  }
  matrix.show();
  while(millis() < loopTime + interval){}
  loopTime += interval;
  M5.update();
}