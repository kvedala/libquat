cmake_minimum_required (VERSION 3.6)
project (libQuat)

set(LIBQUAT_VERSION_MAJOR   0   CACHE STRING "libquat major version number.")
set(LIBQUAT_VERSION_MINOR   1   CACHE STRING "libquat minor version number.")
set(VERSION_PATCH   1   CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

set (CMAKE_BUILD_TYPE RelWithDebInfo)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
# set(CMAKE_CXX_CLANG_TIDY clang-tidy --fix --fix-errors)

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# option (BUILD_SHARED_LIBS "Build the libquat library shared." ON)
# option (BUILD_STATIC_LIBS "Build the libquat library static." ON)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include)

add_compile_definitions(LIBQUAT_MAJOR_VER=${LIBQUAT_VERSION_MAJOR})
add_compile_definitions(LIBQUAT_MINOR_VER=${LIBQUAT_VERSION_MINOR})
# configure_file( "${CMAKE_CURRENT_SOURCE_DIR}/src/libquat.h.in"
#                 "${CMAKE_CURRENT_SOURCE_DIR}/include/libquat.h" )

set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libquat_err.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libquat_vec.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libquat_quat.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libquat_internal.c
)

set(CMAKE_BUILD_STATIC_LIBS ON)
add_compile_definitions(BUILDING_LIBQUAT)
if(BUILD_STATIC_LIBS)
	set(LIBTYPE STATIC)
else ()
	set(LIBTYPE SHARED)
	if (WIN32)
		configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/src/version.rc.in
                ${CMAKE_CURRENT_BINARY_DIR}/src/version.rc @ONLY)
		set (SOURCE_FILES ${SOURCE_FILES} ${CMAKE_CURRENT_BINARY_DIR}/src/version.rc)
    endif()
endif()

cmake_policy(SET CMP0042 NEW)
add_library (libquat ${LIBTYPE} ${SOURCE_FILES})

target_include_directories(libquat BEFORE PUBLIC ${CMAKE_CURRENT_BUILD_DIR}/include)
set_target_properties(libquat PROPERTIES
    LINKER_LANGUAGE C
    VERSION ${LIBQUAT_VERSION_MAJOR}.${LIBQUAT_VERSION_MINOR}
    SOVERSION ${LIBQUAT_VERSION_MAJOR}
    CLEAN_DIRECT_OUTPUT 1)

find_library(M_LIBRARY m)

if(M_LIBRARY)
    target_link_libraries(libquat PUBLIC ${M_LIBRARY})
endif()

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)

install(TARGETS libquat DESTINATION lib)
install(TARGETS libquat EXPORT libuqat_export)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/libquat.h" DESTINATION include)

if(BUILD_DOCUMENTATION)
    ## Configure Doxygen documentation system
    cmake_policy(SET CMP0054 NEW)
    cmake_policy(SET CMP0057 NEW)
    find_package(Doxygen OPTIONAL_COMPONENTS dot dia)
    if(DOXYGEN_FOUND)
        set(DOXYGEN_GENERATE_MAN NO)
        set(DOXYGEN_USE_MATHJAX YES)
        set(DOXYGEN_GENERATE_HTML YES)
        # set(DOXYGEN_HTML_TIMESTAMP YES)
        set(DOXYGEN_EXTRACT_STATIC YES)
        set(DOXYGEN_INLINE_SOURCES YES)
        set(DOXYGEN_CREATE_SUBDIRS YES)
        set(DOXYGEN_GENERATE_TREEVIEW YES)
        set(DOXYGEN_JAVADOC_AUTOBRIEF YES)
        set(DOXYGEN_STRIP_CODE_COMMENTS NO)
        set(DOXYGEN_ENABLE_PREPROCESSING YES)
        set(DOXYGEN_EXT_LINKS_IN_WINDOW YES)
        set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES)
        set(DOXYGEN_CLANG_ASSISTED_PARSING YES)
        set(DOXYGEN_FILE_PATTERNS *.c *.cpp *.h *.md)
        set(DOXYGEN_MATHJAX_EXTENSIONS  TeX/AMSmath TeX/AMSsymbols)
        set(DOXYGEN_TAGFILES "docs/cppreference-doxygen-web.tag.xml=http://en.cppreference.com/w/")
        set(DOXYGEN_MATHJAX_RELPATH "https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.7/MathJax.js?config=TeX-MML-AM_CHTML")
        if(Doxygen_dot_FOUND)
            set(DOXYGEN_HAVE_DOT YES)
            set(DOXYGEN_CALL_GRAPH YES)
            set(DOXYGEN_INTERACTIVE_SVG YES)
            set(DOXYGEN_DOT_IMAGE_FORMAT "svg")
        endif()
        if(OPENMP_FOUND)
            set(DOXYGEN_PREDEFINED "_OPENMP=1")
        endif()
        if(GLUT_FOUND)
            set(DOXYGEN_PREDEFINED ${DOXYGEN_PREDEFINED} "GLUT_FOUND=1")
        endif()

        doxygen_add_docs(
            doc
            ${PROJECT_SOURCE_DIR}
            COMMENT "Generate documentation"
        )
    endif()
endif()
