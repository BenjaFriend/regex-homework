# Regex Homework
This is a homework assignment for IGME 451 on using regex to parse a config file

## Getting Started

There is a submodule for a unit testing library, so make sure that you either
`init` your submodules or just run `bootstrap` on your respective system.

# Windows

This project is using [CMake](https://cmake.org/), with the `CMakeLists.txt
file inside of the root directory of this repo. On Windows you can download
CMake [here](https://cmake.org/download/).

# Linux

Simply run `cmake .` in your current directory, and then `make`.

### How to specify the config file

If you would like to specify your own config file to be pasrsed, then simple
add the command line argument `-C`
