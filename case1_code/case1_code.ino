# include "M5Atom.h"
#include "millisDelay.h" 
float accX, accY, accZ;
const int Interval = 500; // time interval between blinks
unsigned long start = 0; // holds time since begin
uint32_t white = 0xffffff; //white hex num
uint32_t red = 0x00ff00; 
uint32_t black = 0x0000; 
const int pixel_num = 25; // number of pixels 5x5 


void setup() {
  M5.begin(true,false, true); 
  fillScreen(black);
  M5.IMU.Init();
}
void fillScreen(uint32_t color){
  for(int i = 0 ; i < pixel_num; i++)
     M5.dis.drawpix(i,color);
    
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
//      case 0: //  OFF 
//        for(int i = 0; i < pixel_num; i++)
//          M5.Lcd.fillScreen(black);
//          M5.dis.drawpix(i,black); // changes pixel to black
//        break;
        case 0: // Manual Rear strobe (RED)
          CaseRed();
        break;
        case 1: // Manual Rear strobe (WHITE)
          CaseWhite();
        break;
        /*case 2:
          CaseRed();
          M5.IMU.getAccelData(&accX, &accY, &accZ);
          if(accY ...)
            fillScreen(red);
          case 3:
          CaseWhite();
          M5.IMU.getAccelData(&accX, &accY, &accZ);
          if(accY ...)
            fillScreen(white);
          */
          
        default:
            break;
    }
    FSM++;
        if (FSM >= 2)
        {
            FSM = 0;
        }
  }
  delay(50);
  M5.update();
}
void CaseRed(){
   fillScreen(red); // changes pixel to red
   delay(Interval);
  
}
void CaseWhite(){
    fillScreen(white); // changes pixel to white
    delay(Interval);
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
