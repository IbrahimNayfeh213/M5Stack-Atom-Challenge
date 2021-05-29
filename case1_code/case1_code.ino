# include "M5Atom.h"
const int Interval = 500; // time interval between blinks
unsigned long timeSinceBlink = 0; // holds time since begin
uint32_t white = 0xffffff; //white hex num
uint32_t red = 0xff0000; 
const int pixel_num = 25; // number of pixels 5x5
int ledState = LOW;  


void setup() {
  M5.begin(true,false, true); 
}
uint8_t FSM = 0;


void interval_delay(){ // function delay
  unsigned long currentTime = millis();
  if (currentTime - timeSinceBlink >= Interval) {
    timeSinceBlink = currentTime; // save the last time you blinked the LED
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;
 }
}
  
void loop() {
  if(M5.Btn.wasPressed()){
    switch (FSM){
      case 0: // Manual Rear strobe (RED)
        for(int i = 0; i < pixel_num; i++)
          M5.dis.drawpix(i,red); // changes pixel to red
        interval_delay();
        break;
      case 1: // Manual Rear strobe (WHITE)
        for(int i = 0; i < pixel_num; i++)
          M5.dis.drawpix(i,white); // changes pixel to red
        interval_delay();
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
