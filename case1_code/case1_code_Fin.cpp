
# include "M5Atom.h"
# include "millisDelay.h"
unsigned long delayStart = 0;
millisDelay BlinkDelay;
uint32_t red = 0x00ff00;
unsigned long Interval; 

bool ledStat = false;

void checkTurnOffLed() { 
  if (BlinkDelay.justFinished()) { 
    //ledStat = !ledStat;
    BlinkDelay.repeat();
    if(ledStat == true){
      ledStat = false;
    }else{
      ledStat = true;
    }
    if (ledStat)
      M5.dis.fillpix(red); // turn led on red
    else{
      M5.dis.clear(); // turn leds off
    }
  }

}

void setup() {
    M5.begin(true,false, true); 
    M5.dis.fillpix(red);
    M5.dis.setBrightness(20);
    ledStat = true;
    Interval = 500;
    BlinkDelay.start(Interval);
}

void loop() {
   checkTurnOffLed();
   M5.update();
}