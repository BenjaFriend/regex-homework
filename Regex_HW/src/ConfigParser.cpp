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
        static const std::regex sectionReg( "\\[(.+?)\\]\w*" );
        std::smatch section_match;
        std::regex_search( line, section_match, sectionReg );

        if ( section_match.size() )
        {
            AddSection( section_match [ 1 ] );
        }

        // Match key value
        // Keep track of the current section

    }

    file.close();
}

void ConfigParser::AddSection( const std::string & aSectionName )
{
    // If this element does not exist
    if ( ConfigData.find( aSectionName ) == ConfigData.end() )
    {
        Section sec( aSectionName, nullptr );
        ConfigData [ aSectionName ] = sec;
        std::cout << "Add section: " << sec.GetName() << std::endl;
    }
    else
    {
        std::cerr << aSectionName << " already exists!" << std::endl;
    }
}