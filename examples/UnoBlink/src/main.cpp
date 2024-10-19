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
 * @brief  Blink CFSM based Application Example for Arduino 
 *
 * Repository: https://github.com/nhjschulz/cfsm/tree/master/examples/UnoBlink
 */

#include <Arduino.h>
#include <c_fsm.h>

#include "blinkdata.h"
#include "states/OnState.h"

/**
 * @brief CFSM state machine instance
 */
static cfsm_Ctx blinkFsm;

/**
 * @brief Blink application data used by the blink FSM.
 * 
 * Contains the PIN id used for led toggling.
 */
static struct BlinkCtx blinkData = { LED_BUILTIN, 0ull };

/**
 * @brief Arduino setup function
 * 
 */
void setup()
{
  Serial.begin(9600);
  pinMode(blinkData.ledPin, OUTPUT);

  cfsm_init(&blinkFsm, &blinkData);
  cfsm_transition(&blinkFsm, OnState_enter);
}

/**
 * @brief Arduino loop function
 * 
 */
void loop() 
{
  cfsm_process(&blinkFsm);  /* Do work in current CFSM state. */

  /* Turn LED on every 2 seconds by a CFSM event. */
  if ((millis() - blinkData.turnOnTimeMillis) >= 2000ull)
  {
    Serial.println(F("main: turn on time reached"));

    cfsm_event(&blinkFsm, BLINK_EVENT_ON);
  }
}


