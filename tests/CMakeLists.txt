add_executable(libquat_test ${CMAKE_CURRENT_SOURCE_DIR}/test.c)
target_link_libraries(libquat_test PRIVATE libquat)
set_target_properties(libquat_test PROPERTIES
    LINKER_LANGUAGE C
    INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/../include)

add_executable(libquat_test_cxx ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)
target_link_libraries(libquat_test_cxx PRIVATE libquat)
set_target_properties(libquat_test_cxx PROPERTIES
    LINKER_LANGUAGE CXX
    INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/../include)

enable_testing()
add_test(test1 libquat_test)
add_test(test2 libquat_test_cxx)
