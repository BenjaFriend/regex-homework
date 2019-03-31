#include "ConfigParser.h"

ConfigParser::ConfigParser()
{
    ConfigFileName = DEFAULT_CONFIG_FILE;
}

ConfigParser::ConfigParser( const std::string & aConfigFile )
    : ConfigFileName( aConfigFile )
{}

ConfigParser::~ConfigParser()
{
    // #TODO If we need to, clean up any section headers
}

size_t ConfigParser::Run()
{
    std::ifstream file( ConfigFileName, std::ios::in );

    // Use this to keep track of the current section we are in
    std::string CurrentSection = "";

    for ( std::string line; std::getline( file, line ); )
    {
        // Ignore newlines
        if ( line.length() == 0 ) continue;

        std::cout << "Line: " << line << std::endl;

        // Look  for  words between the brackets
        std::smatch isHeader_match = IsSectionHeader( line );
        if ( isHeader_match.size() >= 1 )
        {
            AddSection( isHeader_match [ 1 ] );
            // Keep track of the current header
            CurrentSection = isHeader_match [ 1 ];
            continue;
        }
        
        // Look for a string key val pair
        std::smatch isString_match = IsStringPair( line );
        if ( isString_match.size() >= 1 )
        {
            std::string key = isString_match [ 1 ];
            std::string val = isString_match [ 3 ];
            std::cout << "\tString Key : " << key << " val: " << val << std::endl;
            ConfigData [ CurrentSection ].AddData< std::string >( key, val );
            continue;
        }

    }

    file.close();

    return C_OK;
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

const std::smatch ConfigParser::IsStringPair( const std::string & aSource )
{
    std::smatch string_match;
    static const std::string raw_str = R"((\w+)=(\"(.+?)\"))";
    static const std::regex stringReg( raw_str );
    std::regex_search( aSource, string_match, stringReg );

    return string_match;
}

const std::smatch ConfigParser::IsSectionHeader( const std::string & aSource )
{
    std::smatch section_match;
    static const std::string raw_str = R"(\\[(.+?)\\]\w*)";
    static const std::regex sectionReg( raw_str );
    std::regex_search( aSource, section_match, sectionReg );

    return section_match;
}
