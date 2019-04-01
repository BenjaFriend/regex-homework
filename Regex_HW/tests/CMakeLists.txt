cmake_minimum_required ( VERSION 3.8 )

project( Regex_HW_TESTS LANGUAGES CXX VERSION 0.0.1 )

# Set Build Dir
set( CMAKE_BINARY_DIR    "/build" )
set_property( GLOBAL PROPERTY USE_FOLDERS ON )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/_Output/$<CONFIG> )


# Sets the output directory
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin" )

include_directories( 
	src
	../inc 
	../src
)

# Prepare "Catch" library for other executables
set( CATCH_INCLUDE_DIR   ${CMAKE_CURRENT_SOURCE_DIR}/Catch2/single_include )
add_library ( Catch INTERFACE )
target_include_directories( Catch INTERFACE ${CATCH_INCLUDE_DIR} )


### Setup visual studio source groups / filters ###
file( GLOB_RECURSE _source_list
	src/*.cpp
    ../src/*.cpp* ../src/*.h* ../src/*.hpp*
    ../inc/*.cpp* ../inc/*.h* ../inc/*.hpp*
)

if( MSVC )
    foreach( _source IN ITEMS ${_source_list} )
    	get_filename_component( _source_path "${_source}" PATH )
        string( REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_source_path}" )
        string( REPLACE "/" "\\" _group_path "${_group_path}" )
        source_group( "${_group_path}" FILES "${_source}" )
    endforeach()
endif()

# Make test executable
set( TEST_SOURCES ${_source_list} )
add_executable( tests ${TEST_SOURCES} )
target_link_libraries( tests Catch )

set_property( TARGET tests PROPERTY CXX_STANDARD 14 )
