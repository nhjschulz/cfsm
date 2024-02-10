add_library(Unity STATIC
    src/unity.c
)

target_include_directories(Unity PUBLIC
    src
)