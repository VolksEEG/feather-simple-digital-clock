# feather-simple-digital-clock
  Intended for the Adafruit nRF52840 Feather boards. Tested with the 
  Express version, not on the Sense version (yet)
  
  Continually outputs the following at the period set by PERIOD_MICROSEC in main.cpp:
  1. a "!" character over the feather's hardware serial port
  1. a square wave on pin 10 at the period specified by PERIOD_MICROSEC
  
  NOTE: serial port paud rate is set to 460800, which (I think) is the maximum
  that the Feather's UART can handle. This means it also needs to be set to 460800 
  on the PC side.
  
  feather-simple-digital-clock is designed to be used as a trigger for simple 
  testing of the VolksEEG PC client, e.g. simulating acquisition and display 
  of a set of samples every time a character is received from the Feather. 
  This timing is more accurate than using the standard C# Windows timer, and 
  is a better simulation as it's using serial comms to some degree.
  
  This is currently uses a simple/crummy algorithm -- every time the 
  main loop runs we check to see if sufficient time has passed to change 
  the output. As the loop seems to run roughly 1-2x per mSec, this limits 
  accuracy and max frequency. Would be much better to update this to use a 
  hardware timer interrupt...
