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

/* screen color values */
uint32_t blue = 0x0000ff;
uint32_t green = 0x00ff00;
uint32_t yellow = 0x00ffff;
uint32_t orange = 0xffff00;
uint32_t red = 0xff0000;
uint32_t crntColor;

/* temp vars*/
bool Cels = true;
float tempVal = 0;
float tempUnit = 0;

/* changes between Celsius and Fahrenheit */
float changeUnit(float intTemp){
  float outTemp;
  if(Cels == true){
    outTemp = intTemp;
  }else{
    outTemp = 32 + ((9 * intTemp)/5);
  }
  return(outTemp);
}

/*Function that fills the screen with a certain color*/
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
  } else {
    break;
  }
  return(tColor);
}

void setup() {
  M5.begin(true,false, true);
  M5.IMU.Init();
  Serial.begin(115200);

  matrix.clear();
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(20);
}


void loop() {
  M5.IMU.getTempData(&tempVal);
  tempUnit = changeUnit(tempVal);
  crntColor = currentTempColorC(tempUnit);
  displayTempColor(crntColor);
  matrix.show();
  M5.update();
}