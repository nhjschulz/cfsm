# ******************************************************************************
# Build CFSM as a static link library which is used by example code.
# ******************************************************************************

add_library(cfsm 
    c_fsm.c
)

target_include_directories(cfsm
    PUBLIC "."
)