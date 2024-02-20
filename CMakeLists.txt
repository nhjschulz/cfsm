# ----------------------------------------------------------------------------
#
# Implementing State pattern in C
#
# Copyright (C) 2024  Haju Schulz <haju@schulznorbert.de>
#
cmake_minimum_required(VERSION 3.11)
set (CMAKE_C_STANDARD 99)

project(CFSM
        VERSION 0.1.1
        LANGUAGES C
        DESCRIPTION "A State Design Pattern Approach for C-Programs"
        HOMEPAGE_URL "https://github.com/nhjschulz/cfsm"
)

# ******************************************************************************
# Enable strict compiler warnings 
# ******************************************************************************
 
if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # additional warnings
    add_compile_options(-Wall -Wextra -Wpedantic -save-temps=obj)
endif()

add_subdirectory(src)

set (CFSM_EXAMPLE_MARIO_SRC 
    "examples/mario/main.c"
    "examples/mario/mario.c"
    "examples/mario/states/small_mario.c"
    "examples/mario/states/super_mario.c"
    "examples/mario/states/fire_mario.c"
    "examples/mario/states/cape_mario.c"
    "examples/mario/states/dead_mario.c"
)

add_executable(cfsm_mario ${CFSM_EXAMPLE_MARIO_SRC} )

target_include_directories(cfsm_mario
    PRIVATE "c_fsm"
    PRIVATE "examples/mario"
)
target_link_libraries(cfsm_mario cfsm)

#add_subdirectory(doc)

enable_testing()

add_subdirectory(tests)