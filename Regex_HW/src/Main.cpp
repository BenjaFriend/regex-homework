#include "pch.h"

#include "Utils.h"
#include "ConfigParser.h"

int main( int argc, char* argv [] )
{

    std::string ConfigFilePath;

    // Parse command line arguments
    {
        for ( int i = 0; i < argc; ++i )
        {
            if ( strcmp( argv [ i ], HELP_FLAG ) == 0 )               // Help flag has been passed in
            {
                Utils::PrintHelp();
                return 0;
            }
            else if ( strcmp( argv [ i ], CONFIG_FILE_FLAG ) == 0 )   // Specifying config file
            {
                ConfigFilePath = argv [ i + 1 ];
            }
        }
    }

    std::cout << "Entering the main program with the following config file: " 
        << ConfigFilePath << std::endl;

    // Create the parser
    ConfigParser Parser( ConfigFilePath );

    return 0;
}