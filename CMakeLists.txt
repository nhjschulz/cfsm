# ----------------------------------------------------------------------------
#
# Implementing State pattern in C
#
# Copyright (C) 2024  Haju Schulz <haju@schulznorbert.de>
#
cmake_minimum_required(VERSION 3.11)
set (CMAKE_C_STANDARD 99)

project(c_fsm
        VERSION 0.1.0
        LANGUAGES C
        DESCRIPTION "Finite State machine example"
        HOMEPAGE_URL "https://github.com/nhjschulz/cfsm"
)

add_library(cfsm 
    src/c_fsm/c_fsm.c
)

target_include_directories(cfsm
    PUBLIC "src/c_fsm"
)

add_executable(cfsm_mario
    "src/example/main.c"
    "src/example/mario.c"
    "src/example/states/small_mario.c"
    "src/example/states/super_mario.c"
    "src/example/states/fire_mario.c"
    "src/example/states/cape_mario.c"
    "src/example/states/dead_mario.c"


)
target_include_directories(cfsm_mario
    PRIVATE "c_fsm"
    PRIVATE "src/example"
)
target_link_libraries(cfsm_mario cfsm)

enable_testing()

add_subdirectory(tests)