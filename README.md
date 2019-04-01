```C
/**
* @author   Ben Hoffman ( bah8892@rit.edu )
*/
```

# Regex Homework

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
add the command line argument `-c`

## Assumptions Made

I assume that the user of this parser knows what type of data each key they want
to access is. For example, if they give a config file of:

```
[globals]
playerName="John Doe"
```  
Then I assume that when they want to access `playerName` in C++, they are doing
so as a `std::string`.

To get the data out of the example above, they would need to do the following:
```C++
ConfigParser Parser( ConfigFilePath );
size_t res = Parser.Run();
if ( res == C_OK )
{
    std::string outVal = "";
    Parser [ "globals" ] [ "player" ].GetData( &outVal );
    std::cout << "[globals] outVal : " << outVal << std::endl;
}
```

To see more examples of how to get different types of data, then see `Main.cpp`

## Architecture Overview

The `ConfigParser` is where all `regex` logic is used. The parser has a
map of `Section` objects. The regex logic has been seperated out into `static const`
functions to make them easier to unit test. This does mean that it gets a little
repetetive to parse the config file based on their results, as each function
returns a `std::smatch` object.

A `Section` has a map of `SectionDataElements`, which represents any data parsed
from the config file that was under this header.

Adding data to a `Section` is done using templates, and each `SectionDataElement`
has their own type of data. This makes this scalable for the future to work with
types other than `int`, `bool`, `string`, and `float`. However, this does come
with the caveat of the user needing to know the type of data they want to get out.

## Testing

I wrote some unit tests using the [Catch2](https://github.com/catchorg/Catch2)
library, and they will run and build in Visual Studio as long as you have
run `bootstrap` or initialized submodules.

If you don't want to run the unit tests and want to use your own config file,
than you can use `-c <FILE_NAME>` to  specify a file to use. The config file that
I used is called `test.conf` and is in the root directory.  

**For  Visual Studio** The config file path is relative to the `Regex_HW.vcxproj`,
so you  should put your  config file  in the `regex-homework/build/Regex_HW`  directory.
This is a little odd, as I would have expected it to be relative to the `exe` like
on Linux, but it's not.
