# build for Unity library (https://www.throwtheswitch.org/)
add_subdirectory(Unity-2.5.2)

add_executable(test_c_fsm
    test_c_fsm.c
)

target_link_libraries(test_c_fsm
  Unity
  cfsm
)

add_test(suite_c_fsm, test_c_fsm)