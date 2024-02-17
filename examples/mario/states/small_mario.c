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
 * @brief  Small Mario State Handling
 *  
 *
 * @{
 */

/******************************************************************************
 * Includes
 *****************************************************************************/

#include <stdio.h>

#include "mario.h"

#include "super_mario.h"
#include "cape_mario.h"
#include "fire_mario.h"
#include "dead_mario.h"

#include "small_mario.h"

/******************************************************************************
 * Macros
 *****************************************************************************/

/******************************************************************************
 * Types and Classes
 *****************************************************************************/

/******************************************************************************
 * Prototypes
 *****************************************************************************/

static void SmallMario_onEvent(cfsm_Ctx * state, int eventId);
static void SmallMario_onProcess(cfsm_Ctx * state);
static void SmallMario_onLeave(cfsm_Ctx * state);

/******************************************************************************
 * Variables
 *****************************************************************************/

/******************************************************************************
 * External functions
 *****************************************************************************/

void SmallMario_onEnter(cfsm_Ctx * fsm)
{
    puts("SmallMario_onEnter()...");

    mario_setVariant(SMALL_MARIO);

    fsm->onProcess = SmallMario_onProcess;
    fsm->onEvent = SmallMario_onEvent;
    fsm->onLeave = SmallMario_onLeave;
}

/******************************************************************************
 * Local functions
 *****************************************************************************/

static void SmallMario_onEvent(cfsm_Ctx * fsm, int eventId)
{
    (void)fsm;
    
    mario_updateCoins(eventId);

    switch(eventId)
    {
        case MUSHROOM:
            cfsm_transition(fsm, SuperMario_onEnter);
            break;

        case FIREFLOWER:
            cfsm_transition(fsm, FireMario_onEnter);
            break;

        case FEATHER:
            cfsm_transition(fsm, CapeMario_onEnter);
            break;

        case MONSTER:
            if (0 == mario_takeLife())
            {
                cfsm_transition(fsm, DeadMario_onEnter);
            }
            break;
    }
}

static void SmallMario_onProcess(cfsm_Ctx * fsm)
{
    (void)fsm;

    puts("SmallMario_onProces(): It's me, Mario!");
}

static void SmallMario_onLeave(cfsm_Ctx * fsm)
{
    (void)fsm;
    puts("SmallMario_onLeave() ...");
}

/** @} */