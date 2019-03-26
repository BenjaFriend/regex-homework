# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required ( VERSION 3.8 )
set( CMAKE_SUPPRESS_REGENERATION true )

project ( "Regex_HW" )

# Include sub-projects.
add_subdirectory ( "Regex_HW" )


add_subdirectory ( "Regex_HW/tests" )