# include "M5Atom.h"
# include "millisDelay.h"

uint32_t black = 0x0000; 
uint32_t blue1 = 0x0000ff; // blue color to test
uint32_t L1color = 0xD1EEEE;  // light cyan2
uint32_t L2color = 0xADEAEA;  // turquoise
uint32_t L3color = 0x70DBDB;  // medium turquoise
uint32_t L4color = 0x00CED1;  // dark turquoise (SVG)
uint32_t L5color = 0x00868B;  // turquoise4
millisDelay Delay; 
int interval = 900;

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
    M5.dis.fillpix(black);
    i++; // increments counter
  } 
}
void loop() { 
    switch (i){
      case 0: 
          M5.dis.drawpix(12,blue1); // sets the center pixel to the color we choose
          CheckDelay(); // calls function to check the delay
          break;
      case 1:
          M5.dis.drawpix(7,blue1);
          M5.dis.drawpix(11,blue1);
          M5.dis.drawpix(13,blue1);
          M5.dis.drawpix(17,blue1);
          CheckDelay();
          break;
      case 2:
          M5.dis.drawpix(2,blue1);
          M5.dis.drawpix(6,blue1);
          M5.dis.drawpix(8,blue1);
          M5.dis.drawpix(10,blue1);
          M5.dis.drawpix(14,blue1);
          M5.dis.drawpix(16,blue1);
          M5.dis.drawpix(18,blue1);
          M5.dis.drawpix(22,blue1);
          CheckDelay();
          break;
      case 3: 
          M5.dis.drawpix(1,blue1);
          M5.dis.drawpix(5,blue1);
          M5.dis.drawpix(3,blue1);
          M5.dis.drawpix(9,blue1);
          M5.dis.drawpix(15,blue1);
          M5.dis.drawpix(21,blue1);
          M5.dis.drawpix(23,blue1);
          M5.dis.drawpix(19,blue1);
          CheckDelay();
          break;
      case 4: 
          M5.dis.drawpix(0,blue1);
          M5.dis.drawpix(4,blue1);
          M5.dis.drawpix(20,blue1);
          M5.dis.drawpix(24,blue1);
          CheckDelay();
          break;
      case 5:
          M5.dis.drawpix(0,blue1);
          M5.dis.drawpix(1,blue1);
          M5.dis.drawpix(2,blue1);
          M5.dis.drawpix(3,blue1);
          M5.dis.drawpix(4,blue1);
          M5.dis.drawpix(5,blue1);
          M5.dis.drawpix(9,blue1);
          M5.dis.drawpix(10,blue1);
          M5.dis.drawpix(14,blue1);
          M5.dis.drawpix(15,blue1);
          M5.dis.drawpix(19,blue1);
          M5.dis.drawpix(10,blue1);
          M5.dis.drawpix(20,blue1);
          M5.dis.drawpix(21,blue1);
          M5.dis.drawpix(22,blue1);
          M5.dis.drawpix(23,blue1);
          M5.dis.drawpix(24,blue1);
          CheckDelay();
      case 6:
          M5.dis.drawpix(6,blue1);
          //M5.dis.drawpix(7,blue1);
          //M5.dis.drawpix(8,blue1);
          //M5.dis.drawpix(11,blue1);
          //M5.dis.drawpix(13,blue1);
          //M5.dis.drawpix(16,blue1);
          //M5.dis.drawpix(17,blue1);
          //M5.dis.drawpix(18,blue1);
          //M5.dis.drawpix(19,blue1);
          CheckDelay();
      case 7:
          //M5.dis.drawpix(12,blue1);
          CheckDelay();
      default:
          break;
    }
    
    if(i == 8) 
      i = 0; // resets counter
}
