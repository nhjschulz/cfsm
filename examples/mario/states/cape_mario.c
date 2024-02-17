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
 * @brief  Cape Mario State Handling
 *  
 * @addtogroup MarioExample
 *
 * @{
 */

/******************************************************************************
 * Includes
 *****************************************************************************/

#include <stdio.h>

#include "mario.h"

#include "small_mario.h"
#include "super_mario.h"
#include "fire_mario.h"

#include "cape_mario.h"

/******************************************************************************
 * Macros
 *****************************************************************************/

/******************************************************************************
 * Types and Classes
 *****************************************************************************/

/******************************************************************************
 * Prototypes
 *****************************************************************************/

static void CapeMario_onEvent(cfsm_Ctx * state, int eventId);
static void CapeMario_onProcess(cfsm_Ctx * state);
static void CapeMario_onLeave(cfsm_Ctx * state);

/******************************************************************************
 * Variables
 *****************************************************************************/

/******************************************************************************
 * External functions
 *****************************************************************************/

void CapeMario_onEnter(cfsm_Ctx * fsm)
{
    puts("CapeMario_onEnter()...");

    mario_setVariant(CAPE_MARIO);

    fsm->onProcess = CapeMario_onProcess;
    fsm->onEvent = CapeMario_onEvent;
    fsm->onLeave = CapeMario_onLeave;
}

/******************************************************************************
 * Local functions
 *****************************************************************************/

static void CapeMario_onEvent(cfsm_Ctx * fsm, int eventId)
{
    (void)fsm;
    mario_updateCoins(eventId);

    switch(eventId)
    {
        case MUSHROOM:
            /* noop, I keep being Cape Mario*/
            break;

        case FIREFLOWER:
            cfsm_transition(fsm, FireMario_onEnter);
            break;

        case FEATHER:
            /* Noop, I'm already Cape Mario*/
            break;

        case MONSTER:
            cfsm_transition(fsm, SmallMario_onEnter);
            break;
    }
}

static void CapeMario_onProcess(cfsm_Ctx * fsm)
{
    (void)fsm;
    puts("CapeMario_onProces(): Look, I can fly!");
}

static void CapeMario_onLeave(cfsm_Ctx * fsm)
{
    (void)fsm;
    puts("CapeMario_onLeave() ...");
}

/** @} */
