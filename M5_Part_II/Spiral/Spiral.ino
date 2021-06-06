# include "M5Atom.h"
# include "millisDelay.h"

uint32_t black = 0x0000; 
uint32_t blue1 = 0x0000ff; // blue color to test
uint32_t L1color = 0xccccff;  // light cyan2
uint32_t L2color = 0x9999ff;  // turquoise
uint32_t L3color = 0x6666ff;  // medium turquoise
uint32_t L4color = 0x3232ff;  // dark turquoise (SVG)
uint32_t L5color = 0x0000ff;  // turquoise4
millisDelay Delay; 
millisDelay strobeDelay;
int interval = 900;
int interval2 = 500;

int i = 0; // counter 

void setup() {
    M5.begin(true,false, true); 
    M5.dis.setBrightness(20);
    Delay.start(interval);
}

void CheckDelay(){ // functions that checks if delay ended and sets screen to black
  if(Delay.justFinished())
  {
    Delay.repeat();
    M5.dis.clear();
    i++; // increments counter
  } 
}
void loop() { 
    switch (i){
      case 0: 
        M5.dis.drawpix(12,L1color); // sets the center pixel to the color we choose
        CheckDelay(); // calls function to check the delay
        break;
      case 1: //Inner diamond
        M5.dis.drawpix(7,L2color);
        M5.dis.drawpix(11,L2color);
        M5.dis.drawpix(13,L2color);
        M5.dis.drawpix(17,L2color);
        CheckDelay();
        break;
      case 2:
        M5.dis.drawpix(2,L3color);
        M5.dis.drawpix(6,L3color);
        M5.dis.drawpix(8,L3color);
        M5.dis.drawpix(10,L3color);
        M5.dis.drawpix(14,L3color);
        M5.dis.drawpix(16,L3color);
        M5.dis.drawpix(18,L3color);
        M5.dis.drawpix(22,L3color);
        CheckDelay();
        break;
      case 3: 
        M5.dis.drawpix(1,L4color);
        M5.dis.drawpix(5,L4color);
        M5.dis.drawpix(3,L4color);
        M5.dis.drawpix(9,L4color);
        M5.dis.drawpix(15,L4color);
        M5.dis.drawpix(19,L4color);
        M5.dis.drawpix(21,L4color);
        M5.dis.drawpix(23,L4color);
        CheckDelay();
        break;
      case 4: 
        M5.dis.drawpix(0,L5color);
        M5.dis.drawpix(4,L5color);
        M5.dis.drawpix(20,L5color);
        M5.dis.drawpix(24,L5color);
        CheckDelay();
        break;
      case 5:
        M5.dis.drawpix(0,L5color);
        M5.dis.drawpix(1,L5color);
        M5.dis.drawpix(2,L5color);
        M5.dis.drawpix(3,L5color);
        M5.dis.drawpix(4,L5color);
        M5.dis.drawpix(5,L5color);
        M5.dis.drawpix(9,L5color);
        M5.dis.drawpix(10,L5color);
        M5.dis.drawpix(14,L5color);
        M5.dis.drawpix(15,L5color);
        M5.dis.drawpix(19,L5color);
        M5.dis.drawpix(20,L5color);
        M5.dis.drawpix(21,L5color);
        M5.dis.drawpix(22,L5color);
        M5.dis.drawpix(23,L5color);
        M5.dis.drawpix(24,L5color);
        M5.dis.drawpix(6,L3color);
        M5.dis.drawpix(7,L3color);
        M5.dis.drawpix(8,L3color);
        M5.dis.drawpix(11,L3color);
        M5.dis.drawpix(13,L3color);
        M5.dis.drawpix(16,L3color);
        M5.dis.drawpix(17,L3color);
        M5.dis.drawpix(18,L3color);
        M5.dis.drawpix(12,L1color);
        CheckDelay();
        break;
      case 6:
        M5.dis.clear();
        CheckDelay();
        break;  
      case 7:
        M5.dis.drawpix(0,L5color);
        M5.dis.drawpix(1,L5color);
        M5.dis.drawpix(2,L5color);
        M5.dis.drawpix(3,L5color);
        M5.dis.drawpix(4,L5color);
        M5.dis.drawpix(5,L5color);
        M5.dis.drawpix(9,L5color);
        M5.dis.drawpix(10,L5color);
        M5.dis.drawpix(14,L5color);
        M5.dis.drawpix(15,L5color);
        M5.dis.drawpix(19,L5color);
        M5.dis.drawpix(20,L5color);
        M5.dis.drawpix(21,L5color);
        M5.dis.drawpix(22,L5color);
        M5.dis.drawpix(23,L5color);
        M5.dis.drawpix(24,L5color);
        M5.dis.drawpix(6,L3color);
        M5.dis.drawpix(7,L3color);
        M5.dis.drawpix(8,L3color);
        M5.dis.drawpix(11,L3color);
        M5.dis.drawpix(13,L3color);
        M5.dis.drawpix(16,L3color);
        M5.dis.drawpix(17,L3color);
        M5.dis.drawpix(18,L3color);
        M5.dis.drawpix(12,L1color);
        CheckDelay();
        break;
      case 8:
        M5.dis.drawpix(0,L5color);
        M5.dis.drawpix(1,L5color);
        M5.dis.drawpix(2,L5color);
        M5.dis.drawpix(3,L5color);
        M5.dis.drawpix(4,L5color);
        M5.dis.drawpix(5,L5color);
        M5.dis.drawpix(9,L5color);
        M5.dis.drawpix(10,L5color);
        M5.dis.drawpix(14,L5color);
        M5.dis.drawpix(15,L5color);
        M5.dis.drawpix(19,L5color);
        M5.dis.drawpix(20,L5color);
        M5.dis.drawpix(21,L5color);
        M5.dis.drawpix(22,L5color);
        M5.dis.drawpix(23,L5color);
        M5.dis.drawpix(24,L5color);
        CheckDelay();
        break;
      case 9:
        M5.dis.drawpix(6,L3color);
        M5.dis.drawpix(7,L3color);
        M5.dis.drawpix(8,L3color);
        M5.dis.drawpix(11,L3color);
        M5.dis.drawpix(13,L3color);
        M5.dis.drawpix(16,L3color);
        M5.dis.drawpix(17,L3color);
        M5.dis.drawpix(18,L3color);
        CheckDelay();
        break;
      case 10: 
        M5.dis.drawpix(12,L1color);
        CheckDelay();
        break;
      case 11:
        M5.dis.clear();
        CheckDelay();
        break;   
      default:
        break;
    }
    
    if(i == 12) 
      i = 0; // resets counter
}
