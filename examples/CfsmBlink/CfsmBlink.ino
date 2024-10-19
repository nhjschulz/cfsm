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

cfsm_Ctx blinkFsm;           // CFSM state machine date

uint64_t ledUpdateTime  = 0; // Hold time of last LED update.
int LED_PIN = LED_BUILTIN;   // Used LED Pin

void setup()
{
    pinMode(LED_PIN, OUTPUT);

    // setup FSM and enter LED ON state 
    cfsm_init(&blinkFsm, NULL);
    cfsm_transition(&blinkFsm, LedOnState_enter);
}

void loop() 
{
    cfsm_process(&blinkFsm);  // Do work in current CFSM state 
}

// CFSM On state handler functions

void LedOnState_process(cfsm_Ctx * fsm)
{
    if ((millis() - ledUpdateTime) >= 1000ull)
    {
        // LED On time has expired, switch to off state
        cfsm_transition(fsm, LedOffState_enter);
    }
}

void LedOnState_enter(cfsm_Ctx * fsm)
{
    fsm->onProcess = LedOnState_process; // register state process handler

    digitalWrite(LED_PIN, HIGH); // turn the LED on
    ledUpdateTime = millis();    // store update time
}

// CFSM Off state handler functions

void LedOffState_process(cfsm_Ctx * fsm)
{
    if ((millis() - ledUpdateTime) >= 1000ull)
    {
        // LED Off time has expired, switch to on state
        cfsm_transition(fsm, LedOnState_enter);
    }
}

void LedOffState_enter(cfsm_Ctx * fsm)
{
    fsm->onProcess = LedOffState_process; // register state process handler

    digitalWrite(LED_PIN, LOW); // turn the LED off
    ledUpdateTime = millis();   // store update time
}
