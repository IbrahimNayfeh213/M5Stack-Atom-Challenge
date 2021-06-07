#include <Arduino.h>
#include "M5Atom.h"

//Set up accel varriables 
float accX_avg = 0, accY_avg = 0, accZ_avg = 0;
int n_average = 15;
bool IMU_ready = false;

//Returns screen to black after time
unsigned long display_off_millis;

// timer for the reaction time
unsigned long response_until_time;

// timer for wait a while
unsigned long wait_millis;

int game_state = s_START;

#define CENTER 0
#define LEFT 1
#define RIGHT 2
// if the device was tilted to the left or to the right
int tilt_move = CENTER;

// function to display a number on the LED Matrix screen
// the characters are defined in the fiel "characters.c"
void display_number(uint8_t number) {
    // only single digit numbers between 0 and 9 are possible.
    if (number < 20) {
        M5.dis.displaybuff((uint8_t*)image_numbers[number]);
    }
    else {
        M5.dis.displaybuff((uint8_t*)image_dot);
    }
}

void setup() {
    // start the ATOM device with serial and Display
    // begin(SerialEnable, I2CEnable, DisplayEnable)
    M5.begin(true, false, true);
    delay(50);

    // Average the acceleration data, simple "running average" method without storng the data in an array
    accX_avg = ((accX_avg * (n_average - 1)) + accX) / n_average;
    accY_avg = ((accY_avg * (n_average - 1)) + accY) / n_average;
    accZ_avg = ((accZ_avg * (n_average - 1)) + accZ) / n_average;

    // check if IMU is ready
//    if (M5.IMU.Init() == 0){
//        IMU_ready = true;
//        Serial.println("[OK] INIT ready");
//        M5.dis.displaybuff((uint8_t *)image_CORRECT);
//    } else {
//        IMU_ready = false;
//        Serial.println("[ERR] IMU INIT failed!");
//        M5.dis.displaybuff((uint8_t *)image_WRONG);
//    }
    delay(1000);
    display_off_millis = millis() + 1000;
}

void loop() {
    // if display_off time is reached, switch the display to black
    if (millis() > display_off_millis) {
        fillScreen(cBLACK);
    }
    // get the acceleration data
    // accX = right pointing vector
    //      tilt to the right: > 0
    //      tilt to the left:  < 0
    // accy = backward pointing vector
    //      tilt forward:  < 0
    //      tilt backward: > 0
    // accZ = upward pointing vector
    //      flat orientation: -1g
    float accX = 0, accY = 0, accZ = 0;
    M5.IMU.getAccelData(&accX, &accY, &accZ);
    checkTilt();
    if (tilt_move == LEFT) {
        //ctr--
    }
    if (tilt_move == RIGHT) {
        //ctr++
    }

}

void checkTilt() {
    if (abs(accX_avg) > 0.8 || abs(accY_avg) > 0.8 || abs(accZ_avg) > 0.8) {
        if (abs(accX_avg) > 0.5) { // 0.5g = 45deg tilt angle
            if (accX_avg < -0.5) {
                tilt_move = LEFT;
            }
            if (accX_avg > 0.5) {
                tilt_move = RIGHT;
            }
        }
    }
    else {
        fillScreen(cBLACK);
    }
}