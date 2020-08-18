add_executable(libquat_test test.c)
target_link_libraries(libquat_test PRIVATE libquat)

add_executable(libquat_test_cxx test.cpp)
target_link_libraries(libquat_test_cxx PRIVATE libquat)

# include(CTest)
# add_test(NAME test1 COMMAND libquat_test)
# add_test(NAME test2 COMMAND libquat_test_cxx)
