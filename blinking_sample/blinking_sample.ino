# include "M5Atom.h"
# include "millisDelay.h"
unsigned long delayStart = 0 
uint32_t red = 0x00ff00; // red color
unsigned long Interval = 1000;

bool ledOn = false; // led state boolean 

void setup() {
  M5.begin(true,false, true); 
}

void loop() {
  M5.dis.fillpix(red) // sets screen to red
  ledOn = true;
  delayStart = millis();  // starts delay
  checkLed();
}

/*Checks if delay ended and restarts it*/
void checkLed() { 
  if ((millis() - delayStart) >= Interval)
  {
    delayStart += Interval;
    ledOn = !ledOn;
    if (ledOn)
      M5.dis.fillpix(red); // turn led on red
    else
      M5.dis.clear(); // turn leds off
    
  }
}
