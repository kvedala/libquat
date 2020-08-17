add_executable(libquat_test ${CMAKE_CURRENT_SOURCE_DIR}/test.c)
target_link_libraries(libquat_test PRIVATE libquat)
target_include_directories(libquat_test ${CMAKE_CURRENT_SOURCE_DIR}/../include)

add_executable(libquat_test_cxx ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)
target_link_libraries(libquat_test_cxx PRIVATE libquat)
target_include_directories(libquat_test_cxx ${CMAKE_CURRENT_SOURCE_DIR}/../include)

enable_testing()
add_test(test1 libquat_test)
add_test(test2 libquat_test_cxx)
