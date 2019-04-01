#include "ConfigParser.h"

ConfigParser::ConfigParser()
{
    ConfigFileName = DEFAULT_CONFIG_FILE;
}

ConfigParser::ConfigParser( const std::string & aConfigFile )
    : ConfigFileName( aConfigFile )
{
}

ConfigParser::~ConfigParser()
{
    // #TODO If we need to, clean up any section headers
}

void ConfigParser::ListAllSections()
{
    std::cout << "-------- Sections --------" << std::endl;
    for ( const auto & section : ConfigData )  
        std::cout << section.first << std::endl;
    
    std::cout << "-------------------------" << std::endl;
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

        // Look  for  words between the brackets
        // Match section headers  -------------------------------------
        std::smatch isHeader_match = IsSectionHeader( line );
        if ( isHeader_match.size() >= 1 )
        {
            AddSection( isHeader_match [ 1 ] );
            // Keep track of the current header
            CurrentSection = isHeader_match [ 1 ];
            continue;
        }

        // Match strings  -------------------------------------
        std::smatch isString_match = IsStringPair( line );
        if ( isString_match.size() >= 3 )
        {
            std::string key = isString_match [ 1 ];
            std::string val = isString_match [ 3 ];
            ConfigData [ CurrentSection ].AddData< std::string >( key, val );
            continue;
        }

        // Match bool  -------------------------------------
        std::smatch isBool_Match = IsBoolPair( line );
        if ( isBool_Match.size() >= 1 )
        {
            try
            {
                std::string key = isBool_Match [ 1 ];
                std::string val = isBool_Match [ 2 ];
                bool res = ( val == "true" ? true : false );
                ConfigData [ CurrentSection ].AddData< bool >( key, res );
            }
            catch ( const std::exception & e )
            {
                std::cerr << "Error! " << e.what() << std::endl;
            }
            continue;
        }

        // Match Floats  -------------------------------------
        std::smatch isFloat_Match = IsFloatPair( line );
        if ( isFloat_Match.size() >= 1 )
        {
            try
            {
                std::string key = isFloat_Match [ 1 ];
                std::string val = isFloat_Match [ 2 ];
                std::string::size_type sz;
                float res = std::stof( val, &sz );
                ConfigData [ CurrentSection ].AddData< float >( key, res );
            }
            catch ( const std::exception & e )
            {
                std::cerr << "Error! " << e.what() << std::endl;
            }
            continue;
        }

        // Match ints  -------------------------------------
        std::smatch isInt_Match = IsIntPair( line );
        if ( isInt_Match.size() >= 1 )
        {
            try
            {
                std::string key = isInt_Match [ 1 ];
                std::string val = isInt_Match [ 2 ];
                if ( val.length() > 0 )
                {
                    // Put string value to int
                    std::string::size_type sz;
                    int num = std::stoi( val, &sz );

                    ConfigData [ CurrentSection ].AddData< int >( key, num );
                }
            }
            catch ( const std::exception & e )
            {
                std::cerr << "Error! " << e.what() << std::endl;
            }

            continue;
        }
    }   //  for each line

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

const std::smatch ConfigParser::IsBoolPair( const std::string & aSource )
{
    std::smatch bool_match;
    static const std::string raw_str = R"((\w+)=(true|false))";
    static const std::regex boolReg( raw_str );
    std::regex_search( aSource, bool_match, boolReg );

    return bool_match;
}

const std::smatch ConfigParser::IsFloatPair( const std::string & aSource )
{
    std::smatch float_match;
    static const std::string raw_str = R"((\w+)=(\d*.\d*)f)";
    static const std::regex floatReg( raw_str );
    std::regex_search( aSource, float_match, floatReg );

    return float_match;
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
    // I am using a raw string here because then I don't really need to deal with 
    // the escape characters being used by the compiler instead of regex
    static const std::string raw_str = R"(\[(.*?)\])";
    static const std::regex sectionReg( raw_str );
    std::regex_search( aSource, section_match, sectionReg );

    return section_match;
}

const std::smatch ConfigParser::IsIntPair( const std::string & aSource )
{
    std::smatch int_match;
    static const std::string raw_str = R"((\w+)=(\d*))";
    static const std::regex intReg( raw_str );
    std::regex_search( aSource, int_match, intReg );

    return int_match;
}