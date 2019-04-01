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
        SectionMap & data = Parser.GetData();
        Section & sec = data [ "nums" ];
        SectionDataMap& map = sec.GetData();
        int outNum = 0;
        map [ "num1" ]->GetData( &outNum );
        std::cout << "Num1 isssss : " << outNum << std::endl;
    }
    else
    {
        std::cerr << "There was an error running the config!" << std::endl;
    }


    return 0;
}