cmake_minimum_required ( VERSION 3.8 )

project( Regex_HW_TESTS LANGUAGES CXX VERSION 0.0.1 )

# Set Build Dir
set( CMAKE_BINARY_DIR    "/build" )
set_property( GLOBAL PROPERTY USE_FOLDERS ON )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/_Output/$<CONFIG> )


# Sets the output directory
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin" )

include_directories( ../inc ../src )

# Prepare "Catch" library for other executables
set( CATCH_INCLUDE_DIR   ${CMAKE_CURRENT_SOURCE_DIR}/Catch2/single_include )
add_library ( Catch INTERFACE )
target_include_directories( Catch INTERFACE ${CATCH_INCLUDE_DIR} )

# Make test executable
set( TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/regex-tests.cpp )
add_executable( tests ${TEST_SOURCES} )
target_link_libraries( tests Catch )

set_property( TARGET tests PROPERTY CXX_STANDARD 14 )
