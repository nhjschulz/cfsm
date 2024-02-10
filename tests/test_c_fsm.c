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

/******************************************************************************
 * Prototypes
 *****************************************************************************/

/******************************************************************************
 * Variables
 *****************************************************************************/

static cfsm_Fsm fsm;  /**< fsm instance used in tests */

/******************************************************************************
 * External functions
 *****************************************************************************/

void setUp(void) 
{
    cfsm_init(&fsm);
}

void tearDown(void)
{

}
 
void test_cfsm_init_should_clear_handler()
{
    memset(&fsm, -1, sizeof(fsm));  /* corrupt content */

    cfsm_init(&fsm);
    TEST_ASSERT_EQUAL_PTR(fsm.onEnter, NULL);
    TEST_ASSERT_EQUAL_PTR(fsm.onEvent, NULL);
    TEST_ASSERT_EQUAL_PTR(fsm.onProcess, NULL);
    TEST_ASSERT_EQUAL_PTR(fsm.onLeave, NULL);
}

int main(void)
{
    UNITY_BEGIN();
 
    RUN_TEST(test_cfsm_init_should_clear_handler);
 
    return UNITY_END();
}

/******************************************************************************
 * Local functions
 *****************************************************************************/