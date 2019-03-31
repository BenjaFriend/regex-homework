#pragma once

#include "pch.h"
#include <iostream>


// Command line args
#define HELP_FLAG                   "-h"
#define CONFIG_FILE_FLAG            "-c"
#define DEFAULT_CONFIG_FILE         "test.conf"

namespace Utils
{
    static void PrintHelp() R_UNUSED;

    /// <summary>
    /// Print out the help options for this program. 
    /// </summary>
    static void PrintHelp()
    {
        std::cerr << "Useage: ./Regex_HW [-h] [-c]"     << std::endl;
        std::cerr << "\t-h\tPrint out this useful help message." << std::endl;
        std::cerr << "\t-c\t[Default: " << DEFAULT_CONFIG_FILE << "]\tSpecify the file to use. If not specified the default value of will be used." << std::endl;
    }
}