#include <Arduino.h>
#define PERIOD_MICROSEC 100000

/*
  Outputs a square wave on pin 10 at the period specified by PERIOD_MICROSEC
  the Feather/Arduino seems to run the main loop ~ 1-2x per msec
  which limits resolution and maximum frequency
  much better to do this using a hardware timer interrupt!
*/


uint32_t timeStart = 0;
bool outputState = false;
uint32_t toggleMicrosec = PERIOD_MICROSEC/2;

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(460800);
  pinMode(10, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    if (timeStart == 0) {
    timeStart = micros();
  }

  uint32_t m = micros();
  uint32_t elapsed = m - timeStart;
  if (elapsed > toggleMicrosec) { // check that time is within limits
    if (outputState){
      Serial1.write('!');
      digitalWrite(10, LOW);
      outputState = false;
    }
    else{
      //Serial1.write(' ');
      digitalWrite(10, HIGH);
      outputState = true;
    }
    timeStart = micros();
  }
}
