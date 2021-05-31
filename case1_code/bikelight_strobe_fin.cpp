# include "M5Atom.h"
# include "millisDelay.h"

/*Acceleration variables in the x, y, and z directions*/
float accX, accY, accZ;

/*Time passed for intervalDelay function*/
unsigned long previousT = 0; 

/*Colors in hexadecimal*/
uint32_t white = 0xffffff; 
uint32_t red = 0x00ff00; 
uint32_t black = 0x0000; 

/* strobe settings*/
unsigned long Interval; 
bool ledStat = false;
millisDelay BlinkDelay;

bool IMU_ready = false;

/*Function that checks the time interval and switches the color*/
void checkLed(uint32_t color) { 
  if (BlinkDelay.justFinished()) { 
    BlinkDelay.repeat();
    if(ledStat == true){
      ledStat = false;
    }else{
      ledStat = true;
    }
    if (ledStat)
      M5.dis.fillpix(color); // turn led on red
    else{
      M5.dis.clear(); // turn leds off
    }
  }
}

uint8_t FSM = 0;
uint32_t currentColor = black; 

void setup() {
  M5.begin(true,false, true); 
  M5.dis.clear();
  M5.dis.setBrightness(20);
  ledStat = true;
  Interval = 500;
  BlinkDelay.start(Interval);
  M5.IMU.Init();
}

void loop() {
  
    switch (FSM){
      case 0: //  OFF 
          M5.dis.clear();
          break;
      case 1: // Manual Rear strobe (RED)
          checkLed(red);
          break;
      case 2: // Manual Rear strobe (WHITE)
          checkLed(white);
          break;
      case 3: // Automatic Rear Mode Rear (RED)
          currentColor = red;
          checkLed(currenColor);
          break;
      case 4: // Automatic Rear Mode Rear (WHITE)
          currentColor = white;
          checkLed(currentColor);
          break;  
      default:
          break;
    }
     
    if(FSM == 3 || FSM == 4)
    {
      if (IMU_ready == true) // checks if sensor is ready
      {
        M5.IMU.getAccelData(&accX, &accY, &accZ); // measures acceleration data
        if(accZ*1000 < 0)
          M5.dis.fillpix(currentColor);   // fills color with red if acceleration is less than zero
        else 
          CheckLed(); // otherwise it continues showing strobe lights 
      }
    }
    
   if(M5.Btn.wasPressed()){
    FSM++;
      if (FSM > 4)
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
//
