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
 * This file defines the types and functions used to implement the cfsm 
 * pattern for finite state machines in C-language.
 * 
 * Repository: https://github.com/nhjschulz/cfsm
 *  
 * @addtogroup CFSM
 *
 * @{
 */

#ifndef C_FSM_H_INCLUDED
#define C_FSM_H_INCLUDED

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

struct cfsm_Fsm;

typedef void (*cfsm_TransitionFunction)(struct cfsm_Fsm * state);
typedef void (*cfsm_EventFunction)(struct cfsm_Fsm *state, int eventId);
typedef void (*cfsm_ProcessFunction)(struct cfsm_Fsm *state);

typedef struct cfsm_Fsm {
    cfsm_TransitionFunction onEnter;
    cfsm_TransitionFunction onLeave;
    cfsm_ProcessFunction    onProcess;
    cfsm_EventFunction      onEvent;
} cfsm_Fsm;


/******************************************************************************
 * Functions
 *****************************************************************************/

/**
 * @brief Initialize the given fsm.
 * 
 * @param fsm The fsm data structure
 */
void cfsm_init(struct cfsm_Fsm * fsm);

 /**
  * @brief Transition given fsm to a new state
  * 
  * Perform a state transition be calling the function given by enterFunc. 
  * The called function is expected to update the needed state handlers in
  * the state structure. Unused handlers needs not to be set.
  * Passing NULL as enterfunc triggers the leave handler for the current
  * state and clears all handlers.
  * 
  * @param fsm  The fsm data structure
  * @param enterFunc The enter function for the new fsm state (may be NULL)
  */
void cfsm_transitionTo(struct cfsm_Fsm * fsm, cfsm_TransitionFunction enterFunc);

/**
 * @brief Execute a process cycle to the current fsm state
 * 
 * Call the process handler of the current fsm state. This 
 * function is expected to be called cyclicly. The function
 * does nothing if the current state has no process handler
 * set during enter.
 * 
 * @param fsm The fsm data structure
 */
void cfsm_process(struct cfsm_Fsm * fsm);

/**
 * @brief Signal an event to the current fsm state.
 * 
 * Call the onEvent handler of the current fsm state. This 
 * function is expected to be called when an even shall be
 * signaled to the current state. An event is just an 
 * application defined integer id. It has no meaning to 
 * the fsm itself. Events provide a method to react to
 * application events when they occure instead of polling
 * for them during  process cycles.  
 * 
 * An example for an event id could be a UI button press
 * to trigger a state dependend reaction.
 *  
 * @param fsm The fsm data structure
 * @param eventId An application defined ID to identify the event.
 */
void cfsm_signalEvent(struct cfsm_Fsm * fsm, int eventId);

#ifdef __cplusplus
}
#endif

#endif /* C_FSM_H_INCLUDED */

/** @} */