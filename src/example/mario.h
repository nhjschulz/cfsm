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
 * @brief  Mario CFSM example 
 * 
 * Repository: https://github.com/nhjschulz/cfsm
 *  
 * @addtogroup MarioExample
 *
 * @{
 */
#ifndef MARIO_H_INCLUDED
#define MARIO_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * Includes
 *****************************************************************************/

/******************************************************************************
 * Macros
 *****************************************************************************/

/******************************************************************************
 * Types and Classes
 *****************************************************************************/

/** Events that Mario can face.*/
typedef enum eMarioEvent {
    QUIT,               /**< Exit example app (not a real Mario event) */
    MUSHROOM,           /**< Got a Mushroom                            */
    FIREFLOWER,         /**< Got a fire flower                         */
    FEATHER,            /**< Got a feather                             */
    MONSTER,            /**< Hit a monster                             */
    NOP                 /**< No event ID, used to skip signaling       */
} MarioEvent;

/** Variants Mario can be in (these are the "states") */
typedef enum eMarioVariant {
    SMALL_MARIO,        /**< Small (normal) Mario                      */
    SUPER_MARIO,        /**< Super (big) Mario                         */
    CAPE_MARIO,         /**< Cape Mario which can fly                  */
    FIRE_MARIO,         /**< Fire Mario that throws fire balls         */
    DEAD_MARIO          /**< Game Over or Dead Mario                   */
} MarioVariant;

/** Mario' state data */
typedef struct MarioData {
    MarioVariant variant;  /**< The variant Mario currently has        */
    int lifes;             /**< The number of remaining lifes          */
    int coins;             /**< How many coins we collecred            */
} MarioData;


/******************************************************************************
 * Functions
 *****************************************************************************/

/**
 * @brief  Changes the variant of Mario
 * 
 * @param v the new variant
 */
extern void mario_setVariant(MarioVariant v);

/**
 * @brief Update Marios coins based on the event
 * 
 * @param e the event to get payed for
 */
extern void mario_updateCoins(MarioEvent e);

/**
 * @brief Print the Mario data to the screen
 */
extern void mario_print(void);

/**
 * @brief Take a life from Mario
 * 
 * @return int number of remaining lifes
 */
extern int  mario_takeLife(void);


/******************************************************************************
 * Local functions
 *****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* MARIO_H_INCLUDED */

/** @} */