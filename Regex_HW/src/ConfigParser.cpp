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
    if ( ConfigFileName.length() == 0 )
    {
        std::cerr << "WARNING: NO CONFIG FILE SPECIFED! " << std::endl;
    }
    std::ifstream file( ConfigFileName, std::ios::in );

    // Use this to keep track of the current section we are in
    std::string CurrentSection = "";

    for ( std::string line; std::getline( file, line ); )
    {
        // Ignore newlines
        if ( line.length() == 0 ) continue;

        // Look  for  words between the brackets
        // Match section headers  -------------------------------------
        auto isHeader_match = IsSectionHeader( line );
        if ( isHeader_match.IsValid )
        {
            AddSection( isHeader_match.MatchResult [ 1 ] );
            // Keep track of the current header
            CurrentSection = isHeader_match.MatchResult [ 1 ];
            continue;
        }

        // Match strings  -------------------------------------
        auto isString_match = IsStringPair( line );
        if ( isString_match.IsValid )
        {
            std::string key = isString_match.MatchResult [ 1 ];
            std::string val = isString_match.MatchResult [ 3 ];
            ConfigData [ CurrentSection ].AddData< std::string >( key, val );
            continue;
        }

        // Match bool  -------------------------------------
        auto isBool_Match = IsBoolPair( line );
        if ( isBool_Match.IsValid )
        {
            try
            {
                std::string key = isBool_Match.MatchResult [ 1 ];
                std::string val = isBool_Match.MatchResult [ 2 ];
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
        auto isFloat_Match = IsFloatPair( line );
        if ( isFloat_Match.IsValid )
        {
            try
            {
                std::string key = isFloat_Match.MatchResult [ 1 ];
                std::string signVal = isFloat_Match.MatchResult [ 2 ];
                std::string floatVal = isFloat_Match.MatchResult [ 3 ];

                // get float value from string
                std::string::size_type sz;
                float res = std::stof( floatVal, &sz );

                // Apply sign
                if ( signVal.length() > 0 )                   
                    res *= ( signVal [ 0 ] == '-' ? -1.0f : 1.0f );
                
                // Add data to the current section
                ConfigData [ CurrentSection ].AddData< float >( key, res );
            }
            catch ( const std::exception & e )
            {
                std::cerr << "Error! " << e.what() << std::endl;
            }
            continue;
        }

        // Match ints  -------------------------------------
        MatchRes isInt_Match = IsIntPair( line );
        if ( isInt_Match.IsValid )
        {
            try
            {
                std::string key = isInt_Match.MatchResult [ 1 ];
                std::string val = isInt_Match.MatchResult [ 2 ];
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

const MatchRes ConfigParser::IsBoolPair( const std::string & aSource )
{
    std::smatch bool_match;
    static const std::string raw_str = R"((\w+)=(true|false))";
    static const std::regex boolReg( raw_str );
    std::regex_search( aSource, bool_match, boolReg );

    return  MatchRes( ( bool_match.size() ? true : false ), bool_match );
}

const MatchRes ConfigParser::IsFloatPair( const std::string & aSource )
{
    std::smatch float_match;
    static const std::string raw_str = R"((\w+)=([-+]?)([0-9]*\.[0-9]+|[0-9]+)f)";
    static const std::regex floatReg( raw_str );
    std::regex_search( aSource, float_match, floatReg );    
    
    return MatchRes( ( float_match.size() ? true : false ), float_match );
}

const MatchRes ConfigParser::IsStringPair( const std::string & aSource )
{
    std::smatch string_match;
    static const std::string raw_str = R"((\w+)=(\"(.+?)\"))";
    static const std::regex stringReg( raw_str );
    std::regex_search( aSource, string_match, stringReg );

    return MatchRes( ( string_match.size() ? true : false ), string_match );
}

const MatchRes ConfigParser::IsSectionHeader( const std::string & aSource )
{
    std::smatch section_match;
    // I am using a raw string here because then I don't really need to deal with 
    // the escape characters being used by the compiler instead of regex
    static const std::string raw_str = R"(\[(.*?)\])";
    // (\[\W*(.*?):\W*(.*?)\]) <-- This will check for the sub headings of
    // the regex
    static const std::regex sectionReg( raw_str );
    std::regex_search( aSource, section_match, sectionReg );

    return MatchRes( ( section_match.size() && section_match [ 1 ].length() > 0 ? true : false ), section_match );
}

const MatchRes ConfigParser::IsIntPair( const std::string & aSource )
{
    std::smatch int_match;
    static const std::string raw_str = R"((\w+)=(\d*))";
    static const std::regex intReg( raw_str );
    std::regex_search( aSource, int_match, intReg );

    return MatchRes( ( int_match.size() ? true : false ), int_match );
}