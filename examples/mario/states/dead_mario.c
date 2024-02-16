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
 * @brief  Super Mario State Handling
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

#include "dead_mario.h"

/******************************************************************************
 * Macros
 *****************************************************************************/

/******************************************************************************
 * Types and Classes
 *****************************************************************************/

/******************************************************************************
 * Prototypes
 *****************************************************************************/

static void DeadMario_onProcess(cfsm_Fsm * state);

/******************************************************************************
 * Variables
 *****************************************************************************/

/******************************************************************************
 * External functions
 *****************************************************************************/

void DeadMario_onEnter(cfsm_Fsm * fsm)
{
    puts("DeadMario_onEnter()...");

    mario_setVariant(DEAD_MARIO);

    fsm->onProcess = DeadMario_onProcess;
}

/******************************************************************************
 * Local functions
 *****************************************************************************/

static void DeadMario_onProcess(cfsm_Fsm * fsm)
{
    puts("DeadMario_onProces(): He's dead Jim!");
}