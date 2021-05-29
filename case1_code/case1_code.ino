# include "M5Atom.h"
//#include "millisDelay.h" 
const int Interval = 500; // time interval between blinks
unsigned long start = 0; // holds time since begin
uint32_t white = 0xffffff; //white hex num
uint32_t red = 0x00ff00; 
uint32_t black = 0x00ff00; 
const int pixel_num = 25; // number of pixels 5x5
int ledState = LOW;  


void setup() {
  M5.begin(true,false, true); 
  M5.IMU.Init();
}
uint8_t FSM = 0;

// -- removed this for now 

//void interval_delay(uint32_t color){ // function delay
//  ledDelay.start(Interval);  
//  if(ledDelay.justFinished()) {
//    digitalWrite(led, LOW); // turn led off
//    Serial.println("Turned LED Off");
//  }
//}
  
void loop() {
  if(M5.Btn.wasPressed()){
    switch (FSM){
      case 0: //  OFF Manual Rear strobe (RED)
        for(int i = 0; i < pixel_num; i++){
          M5.dis.drawpix(i,red); // changes pixel to red
          Serial.println(F("Pixel is on"));
        }
        //interval_delay(red);
        delay(Interval);
        break;
      case 1: // Manual Rear strobe (WHITE)
        for(int i = 0; i < pixel_num; i++){
          M5.dis.drawpix(i,white); // changes pixel to white
          Serial.println(F("Pixel is on"));
        }
        //interval_delay(white);
        delay(Interval);
        break;
    }
    FSM++;
        if (FSM >= 4)
        {
            FSM = 0;
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
