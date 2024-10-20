/*
    Blink using a CFSM state machine

    This is a code example for CFSM state machine driven sketches.
    It implements a state pattern version of the simple "blink" sketch.

    Code uses 2 states to turn LED on or off every second.
 
    The circuit:
    * only a board with a builtin LED is required

    Created 20 10 2025
    Haju

    See URL below for further information:
    https://github.com/nhjschulz/cfsm
*/

#include <Arduino.h>
#include <c_fsm.h>

// Forward declaration for entering LED On state
void LedOnState_enter(cfsm_Ctx * fsm);
// Forward declaration for entering LED Off state
void LedOffState_enter(cfsm_Ctx * fsm);

cfsm_Ctx blinkFsm;           // A CFSM state machine.

uint64_t ledUpdateTime  = 0; // Time of last LED update.

const int LED_PIN = LED_BUILTIN;  // Used LED Pin
const int LED_TOGGLE_EVENT = 1;   // Signal LED toggle to FSM.    

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    ledUpdateTime = millis();

    // Setup FSM and enter LED ON state.
    cfsm_init(&blinkFsm, NULL);
    cfsm_transition(&blinkFsm, LedOnState_enter);
}

void loop() 
{
    cfsm_process(&blinkFsm);  // Do work in current state. 

    if ((millis() - ledUpdateTime) >= 1000) {
      ledUpdateTime = millis();

      // Another second has passed, toggle LED on or off.
      cfsm_event(&blinkFsm, LED_TOGGLE_EVENT);
    }
}

// CFSM On state handler functions:

void LedOnState_event(cfsm_Ctx * fsm, int eventId)
{
    if (eventId == LED_TOGGLE_EVENT) {
        // LED On time has expired, switch to OFF state.
        cfsm_transition(fsm, LedOffState_enter);
    }
}

void LedOnState_process(cfsm_Ctx * fsm)
{
  // Add cyclic executed work for this state here.
}

void LedOnState_enter(cfsm_Ctx * fsm)
{
    fsm->onEvent = LedOnState_event;     // Register state event handler.
    fsm->onProcess = LedOnState_process; // Register handler for processing.

    digitalWrite(LED_PIN, HIGH); // Turn the LED on.
}

// CFSM Off state handler functions:

void LedOffState_event(cfsm_Ctx * fsm, int eventId)
{
    if (eventId == LED_TOGGLE_EVENT) {
        // LED Off time has expired, switch to ON state.
        cfsm_transition(fsm, LedOnState_enter);
    }
}

void LedOffState_process(cfsm_Ctx * fsm)
{
  // Add cyclic executed work for this state here.
}

void LedOffState_enter(cfsm_Ctx * fsm)
{
    fsm->onEvent = LedOffState_event;     // Register state event handler.
    fsm->onProcess = LedOffState_process; // Register handler for processing.

    digitalWrite(LED_PIN, LOW); // Turn the LED off.
}
