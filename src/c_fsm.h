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
 * This file defines the types and functions used to implement the CFSM
 * pattern for finite state machines in C-language.
 *
 * Repository: https://github.com/nhjschulz/cfsm
 *
 * @addtogroup CFSM
 *
 * @{
 */

#ifndef SRC_C_FSM_C_FSM_H_
#define SRC_C_FSM_C_FSM_H_

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * Includes
 *****************************************************************************/

/******************************************************************************
 * Macros
 *****************************************************************************/

#define CFSM_VER_MAJOR 0  /**< semantic versioning major  X.x.x */
#define CFSM_VER_MINOR 3  /**< semantic versioning minor  x.X.x */
#define CFSM_VER_PATCH 0  /**< semantic versioning patch  x.x.X */

/******************************************************************************
 * Types and Classes
 *****************************************************************************/

/* forward declaration for typedefs */
struct cfsm_Ctx;

/**
 * @brief Function pointer type for enter/leave operations.
 *
 */
typedef void (*cfsm_TransitionFunction)(struct cfsm_Ctx * fsm);

/**
 * @brief Function pointer type for event signal operation.
 *
 */
typedef void (*cfsm_EventFunction)(struct cfsm_Ctx * fsm, int eventId);

/**
 * @brief  * @brief Function pointer type for cyclic process operation.
 *
 */
typedef void (*cfsm_ProcessFunction)(struct cfsm_Ctx * fsm);

/**
 * @brief Instance data pointer as void * to accept any pointer type.
 *
 */
typedef void *cfsm_InstanceDataPtr;

/** The CFSM context data structure
*/
typedef struct cfsm_Ctx {
    cfsm_InstanceDataPtr    ctxPtr;    /**< Context instance data        */
    cfsm_TransitionFunction onLeave;   /**< Operation to run on leave    */
    cfsm_ProcessFunction    onProcess; /**< Cyclic processoperation      */
    cfsm_EventFunction      onEvent;   /**< Report event to active state */
} cfsm_Ctx;

/******************************************************************************
 * Functions
 *****************************************************************************/

/**
 * @brief Initialize the given fsm.
 *
 * Initialize a cfsm context structure by setting all handlers to NULL
 * and update the instance data pointer with instanceData. Instance data
 * is used if the same operation handlers are used in multiple FSM instances.
 * The handlers can then access the instance data to operate on the actual
 * context.
 *
 * @param fsm The fsm data structure to initialize.
 * @param instanceData Pointer to instance data (may be NULL if unneeded).
 * @since 0.1.0
 */
void cfsm_init(cfsm_Ctx * fsm, cfsm_InstanceDataPtr instanceData);

 /**
  * @brief Transition given fsm to a new state.
  *
  * Perform a state transition by calling the function given by enterFunc.
  * The called function is expected to update the state handlers in
  * the state structure. Unused handlers needs not to be set.
  * Passing NULL as enterfunc triggers the leave handler for the current
  * state and clears all handler which stops the FSM from doing anything.
  *
  * @param fsm  The fsm data structure
  * @param enterFunc The enter operation for the new fsm state (may be NULL)
  * @since 0.1.0
  */
void cfsm_transition(struct cfsm_Ctx * fsm, cfsm_TransitionFunction enterFunc);

/**
 * @brief Execute a process cycle to the current fsm state.
 *
 * Call the process handler of the current fsm state. This
 * function is expected to be called cyclicly. The function
 * does nothing if the current state has no process handler
 * set during enter.
 *
 * @param fsm The fsm data structure
 * @since 0.1.0
 */
void cfsm_process(struct cfsm_Ctx * fsm);

/**
 * @brief Signal an event to the current fsm state.
 *
 * Call the onEvent handler of the current fsm state. This
 * function is expected to be called when an event shall be
 * signaled to the current state. An event is just an
 * application defined integer id. It has no meaning to
 * the FSM itself. Events provide a method to react to
 * application events instead of polling them during
 * process cycles.
 *
 * An example for an event id could be a UI button press
 * to trigger a state dependend reaction.
 *
 * @param fsm The fsm data structure
 * @param eventId An application defined ID to identify the event.
 * @since 0.1.0
 */
void cfsm_event(struct cfsm_Ctx * fsm, int eventId);

#ifdef __cplusplus
}
#endif

#endif /* SRC_C_FSM_C_FSM_H_ */

/** @} */
