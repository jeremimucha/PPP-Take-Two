cmake_minimum_required( VERSION 2.6 )
project( Chapter12 )

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

include_directories( "${PROJECT_SOURCE_DIR}/../GUI" )

find_package( FLTK )
if( FLTK_FOUND )
    include_directories( ${FLTK_INCLUDE_DIR} )
    set( EXTRA_LIBS ${EXTRA_LIBS} ${FLTK_LIBRARIES} )
endif( FLTK_FOUND )

set( EXTRA_LIBS ${EXTRA_LIBS} ${BOOKGUI_LIB} )

file( GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/*.cpp" )

link_directories("${PROJECT_SOURCE_DIR}/../GUI")
link_libraries( "bookgui" )

set( CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-O2 -Wall -Wextra -DNDEBUG" )
set( CMAKE_CXX_STANDARD 14 )

add_executable( fltk_test fltk_test.cpp )
target_link_libraries( fltk_test ${EXTRA_LIBS} )

add_executable( drill drill.cpp )
target_link_libraries( drill ${EXTRA_LIBS} )
