
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

#include "mario.h"

/******************************************************************************
 * Macros
 *****************************************************************************/

/******************************************************************************
 * Types and Classes
 *****************************************************************************/

/**
 * @brief Mario data 
 * 
 * Start with small mario, 3 lifes and no coins
 */
static MarioData mario = 
{
    SMALL_MARIO,
    3,
    0
};

/******************************************************************************
 * Prototypes
 *****************************************************************************/

/******************************************************************************
 * Variables
 *****************************************************************************/

/** Map event Ids to strings for printing */
static char * variantNames[] = {
    "SmallMario",
    "SuperMario",
    "CapeMario",
    "FireMario",
    "DeadMario"
};

/******************************************************************************
 * External functions
 *****************************************************************************/

void mario_setVariant(MarioVariant v)
{
    mario.variant = v;
}

int mario_takeLife()
{
    if (0 != mario.lifes)
    {
        mario.lifes--;
    }

    return mario.lifes;
}

void mario_updateCoins(MarioEvent e)
{
    switch(e)
    {
        case MUSHROOM:
            mario.coins += 100;
            break;

        case FEATHER:
            mario.coins += 300;
            break;

        case FIREFLOWER:
            mario.coins += 200;
            break;

        case MONSTER:
            break;
        
        case QUIT:
        case NOP:
            break;
    }

    if (mario.coins > 5000)
    {
        puts("Mario: One life up!");
        mario.lifes += 1;
        mario.coins -= 5000;
    }
}

extern void mario_print(void)
{
    printf(
        "Mario: Variant: %s Lifes: %d  Coins: %d\n", 
        variantNames[mario.variant],
        mario.lifes,
        mario.coins);
}

int mario_getLifes(void)
{
    puts("Mario: Another life lost!");

    return mario.lifes;
}

/** @} */
