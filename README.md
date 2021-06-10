# M5Stack-Atom-Challenge

## Matrix Challenge Part 1:
   The first part of the project's purpose was to design two different code bases that achieve different behaviours in the M5 Stack Atom Matrix device. This development board is based around the ESP32 PICO processor, has a programmable button, 5x5 RGB LED matrix panel(WS2812C), Built-in Infra-red LED transmitter, Built-in MPU6886 Inertial Sensor, Extendable Pins & Holes, and can be programmed through the Arduino Environment. 
  
### Code 1: Bikelight
   The first part of the challenge is split into two proejcts. The first project's code was written for the M5 Stack Atom Matrix development board to make it function as an automatic brake light for a bicycle, with the mode of the bikelight changing according to its position and acceleration, the modes being:
       
       1- OFF: All LEDs off
       2- Manual Rear strobe (RED): LEDs strobe at a predetermined interval
       3- Manual Front strobe (WHITE): LEDs strobe at a predetermined interval
       4- Automatic Rear Mode Rear (RED): LEDs are solid during a braking event. Return to strobe when riding.
       5- Automatic Front Mode Rear (White): LEDs are solid during a braking event. Return to strobe when riding.
### Code 2: Temperature Tracker + Thermometer
The second project's code base for the M5 Stack Atom Matrix development board to make it function as a multi-purpose thermometer and temperature tracker, that has several modes:

       1- Showing active temperature + units.
       2- Show average of last 24 hours of temperature + Units
       3- Show color scale of temperature range + current temperature as color
       4- Show graph of temperature across a predefined range.
       5- Change units
The libraries needed for the Matrix Challenge Part 1 are:
       
       1- FastLED
       2- SafeString
       
## Matrix Challenge Part 2:
   The second part of the project's purpose had a singular purpose based on an assigned prompt which is was to design "A fidget device that tracks your fidgeting. Create a device that monitors fidgeting and shows information both on the M5 screen and a webpage about the trends of fidgeting. Reassure the user in any way of your choosing. Data must come from as many sources as possible." Much of the code used in the first Matrix Challenge was implemented in the second part due to similar uses and needs in both projects. 
   
   The libraries needed for the Matrix Challenge Part 2 are:
   
      1- WiFi.h
      2- WiFiClient.h
      3- WiFiAP.h
      4- Arduino.h
      5- M5Atom.h
      6- millisDelay.h
      7- characters.c
   

