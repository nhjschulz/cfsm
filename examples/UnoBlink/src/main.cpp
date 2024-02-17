#include <Arduino.h>
#include <c_fsm.h>"

#include "states/OnState.h"

#include "blinkdata.h"

// CFSM state machine data
static cfsm_Ctx blinkFsm;

// Some application data used by the blink FSM
//
static struct BlinkCtx blinkData = { LED_BUILTIN, 0ull };

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  cfsm_init(&blinkFsm, &blinkData);
  cfsm_transition(&blinkFsm, OnState_enter);
}

void loop() 
{
  cfsm_process(&blinkFsm);

  // Turn LED on every 2 seconds by a CFSM event.
  if ((millis() - blinkData.turnOnTimeMillis) >= 2000ull)
  {
    Serial.println(F("main: turn on time reached"));
    cfsm_event(&blinkFsm, BLINK_EVENT_ON);
  }
}
