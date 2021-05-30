
# include "M5Atom.h"
# include "millisDelay.h"
unsigned long delayStart = 0
millisDelay BlinkDelay; 
uint32_t red = 0x00ff00;
unsigned long Interval = 1000; 

bool ledOn = false;


void setup() {
    M5.begin(true,false, true); 
}

void loop() {
   M5.dis.fillpix(red);
   ledOn = true;
   BlinkDelay.start(Interval);
   checkTurnOffLed();

}

void checkTurnOffLed() { 
  if (ledDelay.justFinished()) { 
    BlinkDelay.repeat();
    ledOn = !ledOn
    if (ledOn)
      M5.dis.fillpix(red); // turn led on red
    else{
      M5.dis.clear(); // turn leds off
    }
  }
}
