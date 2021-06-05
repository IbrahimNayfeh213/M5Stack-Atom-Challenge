# include "M5Atom.h"
# include "millisDelay.h"

uint32_t black = 0x0000; 
uint32_t color = 0x0000ff; // blue color to test
uint32_t ligthblue = 0xAEEEEE; // pale turquoise color
millisDelay Delay; 
int interval = 500;

int i = 0; // counter 


void setup() {
    M5.begin(true,false, true); 
    M5.dis.setBrightness(20);
    Delay.start(interval);
}

void CheckDelay(){ // functions that checks if delay ended and sets screen to black
  if(Delay.justFinishe())
  {
    Delay.repeat();
    M5.dis.fillpix(black);
    i++; // increments counter
  } 
}
void loop() { 
    switch (i){
      case 0: 
          M5.dis.drawpix(12,color); // sets the center pixel to the color we choose
          CheckDelay(); // calls function to check the delay
          break;
      case 1:
          M5.dis.drawpix(7,color);
          M5.dis.drawpix(11,color);
          M5.dis.drawpix(13,color);
          M5.dis.drawpix(17,color);
          CheckDelay();
          break;
      case 2:
          M5.dis.drawpix(2,color);
          M5.dis.drawpix(6,color);
          M5.dis.drawpix(8,color);
          M5.dis.drawpix(10,color);
          M5.dis.drawpix(14,color);
          M5.dis.drawpix(16,color);
          M5.dis.drawpix(18,color);
          M5.dis.drawpix(22,color);
          CheckDelay();
          break;
      case 3: 
          M5.dis.drawpix(1,color);
          M5.dis.drawpix(5,color);
          M5.dis.drawpix(3,color);
          M5.dis.drawpix(9,color);
          M5.dis.drawpix(15,color);
          M5.dis.drawpix(21,color);
          M5.dis.drawpix(23,color);
          M5.dis.drawpix(19,color);
          CheckDelay();
          break;
      case 4: 
          M5.dis.drawpix(0,color);
          M5.dis.drawpix(4,color);
          M5.dis.drawpix(20,color);
          M5.dis.drawpix(24,color);
          CheckDelay();
          break;  
      default:
          break;
    }
    
    if(i == 5) 
      i = 0; // resets counter
}
