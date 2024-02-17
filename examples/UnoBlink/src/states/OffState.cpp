#include <Arduino.h>
#include <c_fsm.h>

#include "blinkdata.h"
#include "OnState.h"

static void OffState_onEvent(cfsm_Ctx * fsm, int eventId)
{
    Serial.print(F("OffState: onEvent("));
    Serial.print(eventId);
    Serial.println(F(")"));

    if (BLINK_EVENT_ON == eventId)
    {
        cfsm_transition(fsm, OnState_enter);
    }
}

static void OffState_Leave(struct cfsm_Ctx * fsm)
{
    Serial.println(F("OffState: leave()"));
}

void OffState_enter(cfsm_Ctx * fsm)
{
    BlinkCtxPtr ctx = (BlinkCtxPtr)fsm->ctxPtr;

    Serial.println(F("OffState: enter()"));

    digitalWrite(ctx->ledPin, LOW);  // turn LED off (off state enter)

    fsm->onEvent = OffState_onEvent;
    fsm->onLeave = OffState_Leave;
}
