#include "ConfigParser.h"

ConfigParser::ConfigParser( const std::string & aConfigFile )
    : ConfigFileName( aConfigFile )
{
    Init();
}

void ConfigParser::Init()
{
    std::ifstream file( ConfigFileName, std::ios::in );

    for ( std::string line; std::getline( file, line ); )
    {
        // Ignore newlines
        if ( line.length() == 0 ) continue;

        std::cout << "Line: " << line << std::endl;

        // Look  for  words between the brackets
        static const std::regex sectionReg( "\\[(.+?)\\]" );
        std::smatch section_match;
        std::regex_match( line, section_match, sectionReg );

        for ( size_t i = 0; i < section_match.size(); ++i )
        {
            std::cout << "Regex match: " << section_match [ i ] << std::endl;
        }

        // Match key value
        // Keep track of the current section

    }

    file.close();
}