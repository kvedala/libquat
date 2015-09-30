add_executable(libquat_test ${CMAKE_CURRENT_SOURCE_DIR}/test.c)
target_link_libraries(libquat_test libquat)
set_target_properties(libquat_test PROPERTIES 
    INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/../include"
    LINKER_LANGUAGE C)
