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
 * @brief  CFSM test suite
 *
 * @addtogroup tests
 *
 * @{
 */

/******************************************************************************
 * Includes
 *****************************************************************************/

#include <string.h>
#include <unity.h>

#include "c_fsm.h"

/******************************************************************************
 * Macros
 *****************************************************************************/

/******************************************************************************
 * Types and Classes
 *****************************************************************************/
typedef struct StateOperationCounter_
{
    int enterCalls;
    int leaveCalls;
    int eventCalls;
    int processCalls;
    int lastEventId;
} StateOperationCounter;

/******************************************************************************
 * Prototypes
 *****************************************************************************/
static void State_only_onEnter(cfsm_Ctx * fsm);

static void State_A_onEvent(cfsm_Ctx * fsm, int eventId);
static void State_A_onProcess(cfsm_Ctx * fsm);
static void State_A_onLeave(cfsm_Ctx * fsm);
static void State_A_onEnter(cfsm_Ctx * fsm);

static void State_B_onEvent(cfsm_Ctx * fsm, int eventId);
static void State_B_onProcess(cfsm_Ctx * fsm);
static void State_B_onLeave(cfsm_Ctx * fsm);
static void State_B_onEnter(cfsm_Ctx * fsm);

/******************************************************************************
 * Variables
 *****************************************************************************/

static cfsm_Ctx fsmInstance;  /**< fsm instance used in tests */
static StateOperationCounter state_A;
static StateOperationCounter state_B;
static uint8_t dummyInstanceData = 42u;

/******************************************************************************
 * External functions
 *****************************************************************************/

void setUp(void)
{
    cfsm_init(&fsmInstance, NULL);

    memset(&state_A, 0, sizeof(state_A));
    memset(&state_B, 0, sizeof(state_A));
}

void tearDown(void)
{
}

void test_cfsm_version()
{
    TEST_ASSERT_EQUAL(0, CFSM_VER_MAJOR);
    TEST_ASSERT_EQUAL(2, CFSM_VER_MINOR);
    TEST_ASSERT_EQUAL(0, CFSM_VER_PATCH);
}

void test_cfsm_init_should_clear_handler(void)
{
    memset(&fsmInstance, -1, sizeof(fsmInstance));  /* corrupt content */

    cfsm_init(&fsmInstance, &dummyInstanceData);

    TEST_ASSERT_EQUAL_PTR(NULL, fsmInstance.onEvent);
    TEST_ASSERT_EQUAL_PTR(NULL, fsmInstance.onProcess);
    TEST_ASSERT_EQUAL_PTR(NULL, fsmInstance.onLeave);

    TEST_ASSERT_EQUAL_PTR(&dummyInstanceData, fsmInstance.ctxPtr);

}

void test_cfsm_init_is_safe_to_use(void)
{
    cfsm_init(&fsmInstance, NULL);

    /* should not crash */
    cfsm_process(&fsmInstance);
    cfsm_event(&fsmInstance, 0x12345678);
}

void test_cfsm_transition_should_set_enter_handler_only(void)
{
    cfsm_transition(&fsmInstance, State_only_onEnter);
    TEST_ASSERT_EQUAL_PTR(fsmInstance.onEvent, NULL);
    TEST_ASSERT_EQUAL_PTR(fsmInstance.onProcess, NULL);
    TEST_ASSERT_EQUAL_PTR(fsmInstance.onLeave, NULL);
}

void test_cfs_process()
{
    cfsm_transition(&fsmInstance, State_A_onEnter);

    TEST_ASSERT_EQUAL_INT(state_A.enterCalls, 1);
    TEST_ASSERT_EQUAL_INT(state_A.leaveCalls, 0);
    TEST_ASSERT_EQUAL_INT(state_A.processCalls, 0);
    TEST_ASSERT_EQUAL_INT(state_A.eventCalls, 0);
    TEST_ASSERT_EQUAL_INT(state_A.lastEventId, 0);

    for (int i = 0; i < 10; ++i)
    {
        cfsm_process(&fsmInstance);
        TEST_ASSERT_EQUAL_INT(state_A.lastEventId, i);
    }
    TEST_ASSERT_EQUAL_INT(state_A.enterCalls, 1);
    TEST_ASSERT_EQUAL_INT(state_A.leaveCalls, 0);
    TEST_ASSERT_EQUAL_INT(state_A.processCalls, 10);
    TEST_ASSERT_EQUAL_INT(state_A.eventCalls, 0);
}

void test_cfs_signalEvent()
{
    cfsm_transition(&fsmInstance, State_A_onEnter);

    TEST_ASSERT_EQUAL_INT(state_A.enterCalls, 1);
    TEST_ASSERT_EQUAL_INT(state_A.leaveCalls, 0);
    TEST_ASSERT_EQUAL_INT(state_A.processCalls, 0);
    TEST_ASSERT_EQUAL_INT(state_A.eventCalls, 0);

    for (int i = 0; i < 10; ++i)
    {
        cfsm_event(&fsmInstance, i);
    }
    TEST_ASSERT_EQUAL_INT(state_A.enterCalls, 1);
    TEST_ASSERT_EQUAL_INT(state_A.leaveCalls, 0);
    TEST_ASSERT_EQUAL_INT(state_A.processCalls, 0);
    TEST_ASSERT_EQUAL_INT(state_A.eventCalls, 10);
}

void test_cfs_transition_A_B_A(void)
{
    cfsm_transition(&fsmInstance, State_A_onEnter);

    TEST_ASSERT_EQUAL_PTR(fsmInstance.onEvent, State_A_onEvent);
    TEST_ASSERT_EQUAL_PTR(fsmInstance.onProcess, State_A_onProcess);
    TEST_ASSERT_EQUAL_PTR(fsmInstance.onLeave, State_A_onLeave);

    TEST_ASSERT_EQUAL_INT(state_A.enterCalls, 1);
    TEST_ASSERT_EQUAL_INT(state_A.leaveCalls, 0);
    TEST_ASSERT_EQUAL_INT(state_A.processCalls, 0);
    TEST_ASSERT_EQUAL_INT(state_A.eventCalls, 0);

    TEST_ASSERT_EQUAL_INT(state_B.enterCalls, 0);
    TEST_ASSERT_EQUAL_INT(state_B.leaveCalls, 0);
    TEST_ASSERT_EQUAL_INT(state_B.processCalls, 0);
    TEST_ASSERT_EQUAL_INT(state_B.eventCalls, 0);

    cfsm_transition(&fsmInstance, State_B_onEnter);

    TEST_ASSERT_EQUAL_PTR(fsmInstance.onEvent, State_B_onEvent);
    TEST_ASSERT_EQUAL_PTR(fsmInstance.onProcess, State_B_onProcess);
    TEST_ASSERT_EQUAL_PTR(fsmInstance.onLeave, State_B_onLeave);

    TEST_ASSERT_EQUAL_INT(state_A.enterCalls, 1);
    TEST_ASSERT_EQUAL_INT(state_A.leaveCalls, 1);
    TEST_ASSERT_EQUAL_INT(state_A.processCalls, 0);
    TEST_ASSERT_EQUAL_INT(state_A.eventCalls, 0);

    TEST_ASSERT_EQUAL_INT(state_B.enterCalls, 1);
    TEST_ASSERT_EQUAL_INT(state_B.leaveCalls, 0);
    TEST_ASSERT_EQUAL_INT(state_B.processCalls, 0);
    TEST_ASSERT_EQUAL_INT(state_B.eventCalls, 0);

    cfsm_transition(&fsmInstance, State_A_onEnter);

    TEST_ASSERT_EQUAL_PTR(fsmInstance.onEvent, State_A_onEvent);
    TEST_ASSERT_EQUAL_PTR(fsmInstance.onProcess, State_A_onProcess);
    TEST_ASSERT_EQUAL_PTR(fsmInstance.onLeave, State_A_onLeave);

    TEST_ASSERT_EQUAL_INT(state_A.enterCalls, 2);
    TEST_ASSERT_EQUAL_INT(state_A.leaveCalls, 1);
    TEST_ASSERT_EQUAL_INT(state_A.processCalls, 0);
    TEST_ASSERT_EQUAL_INT(state_A.eventCalls, 0);

    TEST_ASSERT_EQUAL_INT(state_B.enterCalls, 1);
    TEST_ASSERT_EQUAL_INT(state_B.leaveCalls, 1);
    TEST_ASSERT_EQUAL_INT(state_B.processCalls, 0);
    TEST_ASSERT_EQUAL_INT(state_B.eventCalls, 0);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_cfsm_init_is_safe_to_use);
    RUN_TEST(test_cfsm_init_should_clear_handler);
    RUN_TEST(test_cfsm_transition_should_set_enter_handler_only);
    RUN_TEST(test_cfs_transition_A_B_A);

    return UNITY_END();
}

/******************************************************************************
 * Local functions
 *****************************************************************************/
static void State_only_onEnter(cfsm_Ctx * fsm)
{
    (void)fsm;
}

static void State_A_onEnter(cfsm_Ctx * fsm)
{
    fsm->onEvent = State_A_onEvent;
    fsm->onLeave = State_A_onLeave;
    fsm->onProcess = State_A_onProcess;

    state_A.enterCalls++;
}

static void State_A_onEvent(cfsm_Ctx * fsm, int eventId)
{
    (void)fsm;
    (void)eventId;

    state_A.eventCalls++;
}

static void State_A_onProcess(cfsm_Ctx * fsm)
{
    (void)fsm;

    state_A.processCalls++;
}

static void State_A_onLeave(cfsm_Ctx * fsm)
{
    (void)fsm;

    state_A.leaveCalls++;
}

static void State_B_onEnter(cfsm_Ctx * fsm)
{
    fsm->onEvent = State_B_onEvent;
    fsm->onLeave = State_B_onLeave;
    fsm->onProcess = State_B_onProcess;
    state_B.enterCalls++;
}

static void State_B_onEvent(cfsm_Ctx * fsm, int eventId)
{
    (void)fsm;
    (void)eventId;

    state_B.eventCalls++;
}

static void State_B_onProcess(cfsm_Ctx * fsm)
{
    (void)fsm;

    state_B.processCalls++;
}

static void State_B_onLeave(cfsm_Ctx * fsm)
{
    (void)fsm;

    state_B.leaveCalls++;
}
