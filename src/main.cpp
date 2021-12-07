#include <Arduino.h>
//#define TIMER_INTERRUPT_DEBUG         0
//#define _TIMERINTERRUPT_LOGLEVEL_     0
//#include "NRF52TimerInterrupt.h"
//#include "NRF52_ISR_Timer.h"

#define PERIOD_MICROSEC 1000000

/*
  Outputs a square wave on pin 10 at the period specified by PERIOD_MICROSEC
  the Feather/Arduino seems to run the main loop ~ 1-2x per msec
  which limits resolution and maximum frequency
  much better to do this using a hardware timer interrupt!
*/

uint32_t timeStart = 0;
bool outputState = false;
uint32_t toggleMicrosec = PERIOD_MICROSEC/2;
// Init NRF52 timer NRF_TIMER1
//NRF52Timer ITimer(NRF_TIMER_1);

void TimerHandler0()
{
  // Doing something here inside ISR
  Serial1.println("Bing!");
}

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(460800);
  pinMode(10, OUTPUT);
  delay(100);
  
  Serial1.println("Lets go!");
  /*
  if (ITimer.attachInterruptInterval(PERIOD_MICROSEC, TimerHandler0))
  {
    Serial1.println("Attached!");
  }

  {
    Serial.print(F("Starting ITimer0 OK, millis() = ")); Serial.println(millis());
  }
  else
  {
    Serial.println(F("Can't set ITimer0. Select another freq. or timer"));
  } 
  */ 
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
      //Serial1.write('!');
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
