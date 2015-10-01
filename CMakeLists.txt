cmake_minimum_required (VERSION 2.8)

set(LIBQUAT_VERSION_MAJOR   0   CACHE STRING "libquat major version number.")
set(LIBQUAT_VERSION_MINOR   1   CACHE STRING "libquat minor version number.")
# set(VERSION_PATCH   1   CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

project (libquat)
set (CMAKE_BUILD_TYPE Release)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option (BUILD_SHARED_LIBS "Build the libquat library shared." ON)
option (BUILD_STATIC_LIBS "Build the libquat library static." OFF)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include)

FILE (GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

if(BUILD_STATIC_LIBS)
  add_library (libquat STATIC ${SOURCE_FILES})
else (BUILD_SHARED_LIBS)
  add_library (libquat SHARED ${SOURCE_FILES})
endif()

set_target_properties(libquat PROPERTIES 
    LINKER_LANGUAGE   C
    VERSION ${LIBQUAT_VERSION_MAJOR}.${LIBQUAT_VERSION_MINOR}
    SOVERSION ${LIBQUAT_VERSION_MAJOR}
    CLEAN_DIRECT_OUTPUT 1)

if(NOT WIN32)
  find_library(M_LIBRARY
    NAMES m
    PATHS /usr/lib /usr/local/lib
  )
  if(NOT M_LIBRARY)
    message(STATUS
      "math library 'libm' not found - floating point support disabled")
  endif()
else()
  # not needed on windows
  set(M_LIBRARY "")
endif()

target_link_libraries(libquat m)

configure_file( "${CMAKE_CURRENT_SOURCE_DIR}/src/libquat.h.in" 
                "${CMAKE_CURRENT_SOURCE_DIR}/include/libquat.h" )

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

install(TARGETS libquat DESTINATION lib)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/libquat.h" DESTINATION include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
