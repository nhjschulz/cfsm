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
 * @brief  CFSM Header file
 *
 * This file contains the implementation for the cfsm
 * pattern for finite state machines in C-language.
 *
 * Repository: https://github.com/nhjschulz/cfsm
 *
 */

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "c_fsm.h"

/******************************************************************************
 * Macros
 *****************************************************************************/

/******************************************************************************
 * Types and Classes
 *****************************************************************************/

/******************************************************************************
 * Prototypes
 *****************************************************************************/

/******************************************************************************
 * Variables
 *****************************************************************************/

/******************************************************************************
 * External functions
 *****************************************************************************/

void cfsm_init(struct cfsm_Ctx * fsm, cfsm_InstanceDataPtr instanceData)
{
    *fsm = (cfsm_Ctx) {instanceData, 0, 0, 0};
}

void cfsm_transition(struct cfsm_Ctx * fsm, cfsm_TransitionFunction enterFunc)
{
    /* Call former state leave operations if present. */
    if ((cfsm_TransitionFunction)0 != fsm->onLeave)
    {
        fsm->onLeave(fsm);
    }

    /* Clear all handler. They get set by the enter function if needed.
     */
    fsm->onEvent  = (cfsm_EventFunction)0;
    fsm->onLeave  = (cfsm_TransitionFunction)0;
    fsm->onProcess= (cfsm_ProcessFunction)0;

    /* Call enter function NULL checked. It might be NULL to "disable"
     * all FSM operations.
     */
    if ((cfsm_TransitionFunction)0 != enterFunc)
    {
        enterFunc(fsm);
    }
}

void cfsm_process(struct cfsm_Ctx * fsm)
{
    /* Delegate to state processing operation if handler is defined. */
    if ((cfsm_ProcessFunction)0 != fsm->onProcess)
    {
        fsm->onProcess(fsm);
    }
}

void cfsm_event(struct cfsm_Ctx * fsm, int eventId)
{
    /* Delegate to state event processing if handler is defined. */
    if ((cfsm_EventFunction)0 != fsm->onEvent)
    {
        fsm->onEvent(fsm, eventId);
    }
}

/******************************************************************************
 * Local functions
 *****************************************************************************/
