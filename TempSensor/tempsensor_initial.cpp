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
float temp_value;
int x    = matrix.width();
int pass = 0;
const uint16_t white = matrix.Color(255,255,255);
  
void setup() {
  M5.begin(true,false, true);
  M5.IMU.Init();
  M5.dis.clear();
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(white);
}

void loop() {
  M5.IMU.getTempData(&temp_value);
  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  matrix.print(F("TEMP: "));
  matrix.print(temp_value);
  matrix.print(F(" C"));
  if(--x < -96) {
    x = matrix.width();
  }
  matrix.show();
  delay(100);
  M5.update();
}