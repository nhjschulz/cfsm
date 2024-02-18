/* MIT License
 *
 * Copyright (C) 2024  Haju Schulz <haju@schulznorbert.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*******************************************************************************
    DESCRIPTION
*******************************************************************************/

/**
 * @brief  Blink CFSM example: OFF State Implementation
 *
 */

#include <Arduino.h>
#include <c_fsm.h>

#include "blinkdata.h"
#include "OffState.h"

/**
 * @brief Cyclic processing CFSM operaion for ON state
 * 
 * Transition to Off state if time in state is larger/equal 1 second. 
 * 
 * @param fsm CFSM state machine context
 */
static void OnState_process(cfsm_Ctx * fsm)
{
    BlinkCtxPtr ctx = (BlinkCtxPtr)fsm->ctxPtr;

    if ((millis() - ctx->turnOnTimeMillis) >= 1000ull)
    {
        Serial.println(F("OnState: LED On time has expired !"));
        cfsm_transition(fsm, OffState_enter);
    }
}

/**
 * @brief CFSM state leave operation for ON state
 * 
 * Only used to print leave operation to serial log in this example.
 * 
 * @param fsm CFSM state machine context
 */
static void OnState_leave( cfsm_Ctx * fsm)
{
    Serial.println(F("OnState: leave()"));
}

/**
 * @brief CFSM enter operation for ON state
 * 
 * Record time and turn LED on.
 * 
 * @param fsm CFSM state machine context
 */
void OnState_enter(cfsm_Ctx * fsm)
{
    BlinkCtxPtr ctx = (BlinkCtxPtr)fsm->ctxPtr;

    Serial.println(F("OnState: enter()"));

    digitalWrite(ctx->ledPin, HIGH);  /* turn LED on            */
    ctx->turnOnTimeMillis = millis(); /* record time in context */

    /* register ON state hanlders with CFSM */
    fsm->onProcess = OnState_process;
    fsm->onLeave = OnState_leave;
}
