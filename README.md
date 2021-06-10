# M5Stack-Atom-Challenge
This project's first part's purpose was to design two different code bases that achieve different behaviours in the M5 Stack Atom Matrix device.
This development board is based around the ESP32 PICO processor, has a programmable button, 5x5 RGB LED matrix panel(WS2812C), Built-in Infra-red LED transmitter, Built-in MPU6886 Inertial Sensor, Extendable Pins & Holes, and can be programmed through the Arduino Environment. The project is split into two parts. The first part of the code was written for the M5 Stack Atom Matrix development board to make it function as an automatic brake light for a bicycle, with the mode of the bikelight changing according to its position and acceleration, the modes being:

       1- OFF: All LEDs off
       2- Manual Rear strobe (RED): LEDs strobe at a predetermined interval
       3-  Manual Front strobe (WHITE): LEDs strobe at a predetermined interval
       4- Automatic Rear Mode Rear (RED): LEDs are solid during a braking event. Return to strobe when riding.
       5- Automatic Front Mode Rear (White): LEDs are solid during a braking event. Return to strobe when riding.

The second code base for the M5 Stack Atom Matrix development board to make it function as a multi-purpose thermometer and temperature tracker, that has several modes:

       1- Showing active temperature + units.
       2- Show average of last 24 hours of temperature + Units
       3- Show color scale of temperature range + current temperature as color
       4- Show graph of temperature across a predefined range.
       5- Change units


