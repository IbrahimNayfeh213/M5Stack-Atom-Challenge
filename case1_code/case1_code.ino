# include "M5Atom.h"

/*Acceleration variables in the x, y, and z directions*/
float accX, accY, accZ;
float accXAvg;
int n;
/*Time interval for blinks*/
unsigned long Interval = 1000; 
/*Time passed for intervalDelay function*/
unsigned long previousT = 0; 

/*Colors in hexadecimal*/
uint32_t white = 0xffffff; 
uint32_t red = 0x00ff00; 
uint32_t black = 0x0000; 

/* number of pixels 5x5 */
const int pixel_num = 25; 


void setup() {
  M5.begin(true,false, true); 
  fillScreen(black);
  M5.IMU.Init();
}

/*Function that fills the screen with a certain color*/
void fillScreen(uint32_t color){
  for(int i = 0 ; i < pixel_num; i++)
     M5.dis.drawpix(i,color);
    
}

uint8_t FSM = 0;

/*Time Delay function */
void intervalDelay(uint32_t color){  
  unsigned long currentT = millis();
  if(currentT - previousT >= Interval){ // if time from start reached 1000 mili seconds the screen will be filled with black 
     fillScreen(black);
     previousT = currentT; // updates time for the next loop
     fillScreen(color); // fills the screen back if the original color
  }
  
}
  
void loop() {
  uint32_t currentColor = black;
  if(M5.Btn.wasPressed()){
    switch (FSM){
      case 0: //  OFF 
          fillScreen(currentColor); // changes pixel to black
        break;
      case 1: // Manual Rear strobe (RED)
          currentColor = red;
          fillScreen(currentColor);
        break;
      case 2: // Manual Rear strobe (WHITE)
          currentColor = white;
          fillScreen(currentColor);
        break;
      case 3: // Automatic Rear Mode Rear (RED)
          currentColor = red;
          fillScreen(currentColor);
      case 4: // Automatic Rear Mode Rear (WHITE)
          currentColor = white;
          fillScreen(currentColor);
      default:
            break;
    }
    FSM++;
    if (FSM >= 5)
       FSM = 0;
  }
  
  intervalDelay(currentColor);
  
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
//       fillScrean(currentColor);
//  }
  
  M5.update();
}

///*Shows Blinking Red Screen */
//void CaseRed(){
//   fillScreen(red); // changes pixel to red
//   intervalDelay();
//  
//}
//
///*Shows Blinking White Screen */
//void CaseWhite(){
//    fillScreen(white); // changes pixel to white
//    intervalDelay();
//}


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
