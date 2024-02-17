#include <c_fsm.h>

#include "blinkdata.h"
#include "OffState.h"


static void OnState_process(cfsm_Ctx * fsm)
{
    BlinkCtxPtr ctx = (BlinkCtxPtr)fsm->ctxPtr;

    if ((millis() - ctx->turnOnTimeMillis) >= 1000ull)
    {
        Serial.println(F("OnState: LED On time has expired !"));
        cfsm_transition(fsm, OffState_enter);
    }
}

static void OnState_leave( cfsm_Ctx * fsm)
{
    Serial.println(F("OnState: leave()"));
}

void OnState_enter(cfsm_Ctx * fsm)
{
    BlinkCtxPtr ctx = (BlinkCtxPtr)fsm->ctxPtr;

    Serial.println(F("OnState: enter()"));

    digitalWrite(ctx->ledPin, HIGH);  // turn LED on (on state enter)
    ctx->turnOnTimeMillis = millis();

    fsm->onProcess = OnState_process;
    fsm->onLeave = OnState_leave;
}
