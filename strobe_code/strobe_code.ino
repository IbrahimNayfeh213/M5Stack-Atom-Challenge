# include "M5Atom.h"
# include "millisDelay.h"

/*Acceleration variables in the x, y, and z directions*/
float accX, accY, accZ;
float accXAvg;
int nAvg;

/*Time interval for blinks*/
unsigned long Interval = 1000; 
/*Time passed for intervalDelay function*/
unsigned long previousT = 0; 
millisDelay BlinkDelay;


/*Colors in hexadecimal*/
uint32_t white = 0xffffff; 
uint32_t red = 0x00ff00; 
uint32_t black = 0x0000; 

bool Ledstate = false;

/*Modes Counter*/
uint8_t FSM = 0;

/*Time Delay function */
void CheckLed(){  
  if(BlinkDelay.justfinished(0)){
    if (Ledstate)
        Ledstate = false;
    else 
        Ledstate = true;
  BlinkDelay.repeat();
}



void setup() {
  M5.begin(true,false, true); 
  M5.dis.setBrightness(20);
  fillScreen(black);
  BlinkDelay.start(Interval);
  M5.IMU.Init();
}


void loop() 
{
 
    switch (FSM)
    {
      case 0: //  OFF 
          M5.dis.fillpix(black); // changes pixel to black
        break;
        
      case 1: // Manual Rear strobe (RED)
          if (ledstate)
             M5.dis.clear() 
          else
             M5.dis.fillpix(red); 
        break;
        
      case 2: // Manual Rear strobe (WHITE)
            if (ledstate)
             M5.dis.clear() 
          else
             M5.dis.fillpix(white); 
        break;
        
      case 3: // Automatic Rear Mode Rear (RED)
           if (ledstate)
             M5.dis.clear() 
          else
             M5.dis.fillpix(red); 
        break;
      case 4: // Automatic Rear Mode Rear (WHITE)
           if (ledstate)
             M5.dis.clear() 
           else
             M5.dis.fillpix(white); 
        break;
       default:
            break;
    }
    
    CheckLed();
  
  if(M5.Btn.wasPressed())
  {
    FSM++;
    if(FSM >= 5)
      FSM = 0;
  }
  

  
//  if(FSM == 3 || FSM == 4){
//    M5.IMU.getAccelData(&accX, &accY, &accZ);
//    float initalAcc = *accX;
//    for(int i = 0; i < n;i++){
//      
//      
//      
//    }
//    float initalAcc = ;
//    accXAvg = ((accXAvg * (n-1))+accX)/n;
//    if( - <= -0.115)
//       fillScreen(currentColor);
//  }
  
  M5.update();
}
