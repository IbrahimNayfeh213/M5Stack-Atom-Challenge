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

/*Function that fills the screen with a certain color*/
void fillScreen(uint32_t color){
     M5.dis.fillpix(color);
}

/*Function that checks the time interval and switches the color*/
void checkTurnOffLed(uint32_t color) { 
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
  M5.IMU.getAccelData(&accX, &accY, &accZ);
    switch (FSM){
      case 0: //  OFF 
          M5.dis.clear();
          break;
      case 1: // Manual Rear strobe (RED)
          checkTurnOffLed(red);
          break;
      case 2: // Manual Rear strobe (WHITE)
          checkTurnOffLed(white);
          break;
      case 3: // Automatic Rear Mode Rear (RED)
          if(accZ*1000 > 0.1){
            checkTurnOffLed(red);
          } else {
            M5.dis.fillpix(red);
          }
          break;
      case 4: // Automatic Rear Mode Rear (WHITE)
          if(accZ*1000 > 0.1){
            checkTurnOffLed(white); 
          } else {
            M5.dis.fillpix(white);
          }
          break;  
      default:
          break;
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
