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
 * @brief  Blink CFSM example: ON State Implementation
 *
 */

#include <Arduino.h>
#include <c_fsm.h>

#include "blinkdata.h"
#include "OnState.h"

/**
 * @brief CFSM event operation for OFF state
 * 
 * React on led ON event to transition to ON state.
 * 
 * @param fsm CFSM state machine context
 * @param eventId event ID
 */
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

/**
 * @brief CFSM state leave operation for Off state
 * 
 * Only used to print leave operation to serial log in this example.
 * 
 * @param fsm CFSM state machine context
 */
static void OffState_Leave(struct cfsm_Ctx * fsm)
{
    Serial.println(F("OffState: leave()"));
}

/**
 * @brief CFSM enter operation for OFF state
 * 
 * Turn LED off.
 * 
 * @param fsm CFSM state machine context
 */
void OffState_enter(cfsm_Ctx * fsm)
{
    BlinkCtxPtr ctx = (BlinkCtxPtr)fsm->ctxPtr;

    Serial.println(F("OffState: enter()"));

    digitalWrite(ctx->ledPin, LOW);  /* turn LED off */

    /* register OFF state hanlders with CFSM */
    fsm->onEvent = OffState_onEvent;
    fsm->onLeave = OffState_Leave;
}
