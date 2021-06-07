#include <Arduino.h>
#include "M5Atom.h"
#include "millisDelay.h"
#include "characters.c"
//bool IMU_ready = false;

//Set up accel varriables 
float accX = 0, accY = 0, accZ = 0;
float accX_avg = 0, accY_avg = 0, accZ_avg = 0;
int n_average = 15;

//Define tilt options and orient Matrix
#define CENTER 0
#define LEFT 1
#define RIGHT 2
int tilt_move = CENTER;

//Define counter variables 
int modeCtr = 0;

//Define colors
uint32_t white = 0xffffff;
uint32_t red = 0x00ff00;
uint32_t black = 0x0000;
#define cBLACK 0

//Set up wait for change
unsigned long interval = 6000;
millisDelay waitDelay;

//Display numbers of modes
void display_number(uint8_t number) {
    if (number < 20) {
        M5.dis.displaybuff((uint8_t*)image_numbers[number]);
    }
    else {
        M5.dis.displaybuff((uint8_t*)image_dot);
    }
}

//Checks if the Matrix has been tilted
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
    //  else {
    //    M5.dis.clear();
    //  }
}

void checkDelay() {
    if (waitDelay.justFinished()) {
        M5.dis.clear();
    }
    else {}
}

void checkCtr() {
    if (tilt_move == LEFT) {
        modeCtr--;
    }
    if (tilt_move == RIGHT) {
        modeCtr++;
    }
}

void setup() {
    M5.begin(true, false, true);
    // Average the acceleration data, simple "running average" method without storng the data in an array
    accX_avg = ((accX_avg * (n_average - 1)) + accX) / n_average;
    accY_avg = ((accY_avg * (n_average - 1)) + accY) / n_average;
    accZ_avg = ((accZ_avg * (n_average - 1)) + accZ) / n_average;
}

void loop() {
    M5.IMU.getAccelData(&accX, &accY, &accZ);
    checkTilt();
    checkCtr();
    switch (modeCtr) {
    case 0: //Passive read
        display_number(modeCtr);
        break;
    case 1: //Show active temp
        display_number(modeCtr);
        break;
    case 2: //Avg of 24 hours
        display_number(modeCtr);
        break;
    case 3: //Color scale of temp and current temp color
        display_number(modeCtr);
        break;
    case 4: //Graph of temp across range
        display_number(modeCtr);
        break;
    case 5: //Change units 
        display_number(modeCtr);
        break;
    }
}