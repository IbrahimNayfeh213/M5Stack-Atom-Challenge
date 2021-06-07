#include "M5Atom.h"
#include "millisDelay.h"
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

/* Set up text display*/
#define PIN 27

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(5, 5, PIN,
    NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
    NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
    NEO_GRB + NEO_KHZ800);

/* text vars */
const uint16_t textWhite = matrix.Color(255, 255, 255);
int x = matrix.width();
int pass = 0;

/*variable declaration*/
float tempVal;
int minVal[60];
int hourVal[24];
int minCtr;
int hourCtr = 0;
int minAvg = 0;
int hourAvg = 0;
millisDelay ReadDelay;
int interval = 60000;

void printHourAvg() {
    if (M5.Btn.wasPressed()) {
        if (hourCtr > 0) {
            matrix.print(F("HOUR AVG: "));
            matrix.print(hourVal[hourCtr]);
        }
        else {
            matrix.print(F("AVG: "));
            matrix.print(minAvg);
        }
    }
}

void setup() {
    M5.begin(true, false, true);
    M5.IMU.Init();
    M5.dis.clear();
    Serial.begin(115200);
    Serial.println("Temperature Data");
    //Serial.print(unit);
    //Serial.print('/n');
    ReadDelay.start(interval);

    //  matrix.begin();
    //  matrix.setTextWrap(false);
    //  matrix.setBrightness(20);
    //  matrix.setTextColor(textWhite);
}

void loop() {
    for (minCtr = 0; minCtr < 60; minCtr++) {
        if (ReadDelay.justFinished()) {
            ReadDelay.repeat();
            M5.IMU.getTempData(&tempVal);
            minVal[minCtr] = tempVal;
            minAvg += minVal[minCtr];
            Serial.print(tempVal, 2);
            Serial.print(", ");
        }
    }
    //  printHourAvg();
    if (minCtr >= 60) {
        hourVal[hourCtr] = minAvg;
        hourCtr++;
        minAvg = 0;
    }
    minCtr = 0;
}

/* Read every min, average every hour and every day
*/