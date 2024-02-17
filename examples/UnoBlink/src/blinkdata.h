#include <Arduino.h>

// FSM application instance data
typedef struct BlinkCtx {
    int ledPin;
    uint64_t turnOnTimeMillis;
} BlinkCtx, * BlinkCtxPtr ;


enum BlinkEvents {
    BLINK_EVENT_ON = 42
};