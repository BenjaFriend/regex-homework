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
    size_t res = Parser.Run();

    if ( res == C_OK )
    {
        std::cout << "===================== Examples =================" << std::endl;
        SectionMap & fileData = Parser.GetData();

        // Example of loading an INT from a section called "nums"
        {
            // Just pass in a ref to the variable to populate...
            int outNum = 0;
            Parser [ "nums" ] [ "num1" ].GetData( &outNum );

            std::cout << "[int] outNum : " << outNum << std::endl;
        }

        // Example of loading a FLOAT from a section called "video"
        {
            float outVal = 0.0f;
            Parser [ "video" ] [ "scalefactor" ].GetData( &outVal );
            std::cout << "[float] outVal : " << outVal << std::endl;
        }

        // Example of loading a STRING from a section called "globals"
        {
            std::string outVal = "";
            Parser [ "globals" ] [ "player" ].GetData( &outVal );
            std::cout << "[string] outVal : " << outVal << std::endl;
        }

        // Example of loading a BOOL from a section called "video"
        {
            bool outVal;
            Parser [ "video" ] [ "multidisplay" ].GetData( &outVal );
            std::cout << "[bool] outVal : " << outVal << std::endl;
        }

        Parser.ListAllSections();
        Parser [ "video" ].ListData();
    }
    else
    {
        std::cerr << "There was an error running the config!" << std::endl;
    }

    return 0;
}