cmake_minimum_required (VERSION 2.8)

set(LIBQUAT_VERSION_MAJOR   0   CACHE STRING "libquat major version number.")
set(LIBQUAT_VERSION_MINOR   1   CACHE STRING "libquat minor version number.")
set(VERSION_PATCH   1   CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

project (libQuat)
set (CMAKE_BUILD_TYPE RelWithDebInfo)

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# option (BUILD_SHARED_LIBS "Build the libquat library shared." ON)
option (BUILD_STATIC_LIBS "Build the libquat library static." ON)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include)

configure_file( "${CMAKE_CURRENT_SOURCE_DIR}/src/libquat.h.in"
                "${CMAKE_CURRENT_SOURCE_DIR}/include/libquat.h" )

FILE (GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

if(BUILD_STATIC_LIBS)
	set(LIBTYPE STATIC)
else (BUILD_SHARED_LIBS)
	set(LIBTYPE SHARED)
	if (WIN32)
		configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/src/version.rc.in
                ${CMAKE_CURRENT_BINARY_DIR}/src/version.rc @ONLY)
		set (SOURCE_FILES ${SOURCE_FILES} ${CMAKE_CURRENT_BINARY_DIR}/src/version.rc)
	endif()
endif()

cmake_policy(SET CMP0042 NEW)
add_library (libquat ${LIBTYPE} ${SOURCE_FILES})

set_target_properties(libquat PROPERTIES
    LINKER_LANGUAGE C
    VERSION ${LIBQUAT_VERSION_MAJOR}.${LIBQUAT_VERSION_MINOR}
    SOVERSION ${LIBQUAT_VERSION_MAJOR}
    CLEAN_DIRECT_OUTPUT 1)

find_library(M_LIBRARY m)

if(M_LIBRARY)
    target_link_libraries(libquat ${M_LIBRARY})
endif()

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

if(BUILD_DOCUMENTATION)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()

    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${doxyfile_in} ${doxyfile} @ONLY)

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)

    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc)
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)

install(TARGETS libquat DESTINATION lib)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/libquat.h" DESTINATION include)

