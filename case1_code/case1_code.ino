# include "M5Atom.h"
const int Interval = 500; // time interval between blinks
unsigned long timeSinceBlink = 0; // holds time since begin
uint32_t white = 0xFFFFFF; //white hex num
const int pixel_num = 25; // number of pixels 5x5
int ledState = LOW;  


void setup() {
  M5.begin(true,false, true); 
}

void loop() {
  //case 1 - not added the clicking function
  for(int i = 0; i < pixel_num; i++)
    M5.dis.drawpix(i,white); // changes pixel to white

  unsigned long currentTime = millis();
  
  if (currentTime - timeSinceBlink >= Interval) {
    timeSinceBlink = currentTime; // save the last time you blinked the LED
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
  }
}
