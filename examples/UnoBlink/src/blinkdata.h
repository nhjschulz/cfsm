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
 * @brief  Blink CFSM example: Instance data and Event definitions
 *
 */

#ifndef SRC_C_BLINKDATA_C_BLINKDATA_H_
#define SRC_C_BLINKDATA_C_BLINKDATA_H_

#include <Arduino.h>

/**
 * @brief Blink FSM application instance data
 * 
 */
typedef struct BlinkCtx {
    int ledPin;                 /**< Arduino Led pin number              */
    uint64_t turnOnTimeMillis;  /**< Tick time when we turned the Led on */
} BlinkCtx, * BlinkCtxPtr ;

/**
 * @brief Events understood by the FSM
 * 
 */
enum BlinkEvents {
    BLINK_EVENT_ON = 42    /**< Led turn on event ID*/
};

#endif /* SRC_C_BLINKDATA_C_BLINKDATA_H_ */