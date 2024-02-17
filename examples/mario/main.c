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
 * @brief  CFSM Mario state handling example
 *  
 * @addtogroup MarioExample
 *
 * @{
 */

/******************************************************************************
 * Includes
 *****************************************************************************/

#include <stdio.h>
#include "c_fsm.h"

#include "mario.h"
#include "states/small_mario.h"


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

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    
    cfsm_Ctx marioFsm;

    puts ("Mario cfsm example: \n");

    cfsm_init(&marioFsm, NULL);
    cfsm_transition(&marioFsm, SmallMario_onEnter);

    for(;;) 
    {
        int option;

        /* perform process cycle in current CFSM state.*/
        cfsm_process(&marioFsm);

        mario_print(); /* show Mario's data*/

        printf("\nChoose Event: (1=Mushroom, 2=FireFlower, 3=feather, "
               "4=Monster, 5=none (just process), 0=quit) : ");
        while ((scanf("%d", &option) != 1) || (option > 5))
        {
            puts("invalid option");
        }

        if (QUIT == option) {
            break;
        }

        /* process signal in current CFSM state */
        if (NOP != option) 
        {
            cfsm_event(&marioFsm, option);
        }
    }

    return 0;
}

/******************************************************************************
 * Local functions
 *****************************************************************************/

/** @} */
