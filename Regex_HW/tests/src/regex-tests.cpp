#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch2/catch.hpp"

#include "pch.h"
#include <regex>
#include <string>

#include "ConfigParser.h"

TEST_CASE( "Section Header", "[headers]" )
{
    SECTION( "Valid Headers" )
    {
        {
            auto res0 = ConfigParser::IsSectionHeader( "[header]" );
            REQUIRE( res0.IsValid );

            auto res1 = ConfigParser::IsSectionHeader( "[header:subheader]" );
            REQUIRE( res1.IsValid );

            auto res2 = ConfigParser::IsSectionHeader( "[header:subheader]    #  Comment time!" );
            REQUIRE( res2.IsValid );
        }
    }

    SECTION( "Invalid Headers" )
    {
        {
            auto res0 = ConfigParser::IsSectionHeader( "header" );
            REQUIRE( !res0.IsValid );

            auto res1 = ConfigParser::IsSectionHeader( "# this is a comment!" );
            REQUIRE( !res1.IsValid );

            auto res2 = ConfigParser::IsSectionHeader( "42" );
            REQUIRE( !res2.IsValid );

            auto res3 = ConfigParser::IsSectionHeader( "[]" );
            REQUIRE( !res3.IsValid );
        }
    }
}

TEST_CASE( "String Key Pair", "[String]" )
{
    SECTION( "Valid String Pairs" )
    {
        {
            auto valid = "resolution=\"1080x700\"";
            auto res = ConfigParser::IsStringPair( valid );
            REQUIRE( res.IsValid );
        }
        {
            auto valid = "chartype=\"blue tower\"";
            auto res = ConfigParser::IsStringPair( valid );
            REQUIRE( res.IsValid );
        }

        {
            auto valid = "chartype=\"blue tower 4242 z\"";
            auto res = ConfigParser::IsStringPair( valid );
            REQUIRE( res.IsValid );
        }
        {
            auto valid = "chartyp56_e=\"blue tower 4242 z\"";
            auto res = ConfigParser::IsStringPair( valid );
            REQUIRE( res.IsValid );
        }
        {
            auto valid = "chartyp56_e=\"blue tower# ## 4242 z\"";
            auto res = ConfigParser::IsStringPair( valid );
            REQUIRE( res.IsValid );
        }
    }

    SECTION( "Invalid String Pairs" )
    {
        {
            auto invalid = "resolution=";
            auto res = ConfigParser::IsStringPair( invalid );
            REQUIRE( !res.IsValid );
        }
        {
            auto invalid = "=";
            auto res = ConfigParser::IsStringPair( invalid );
            REQUIRE( !res.IsValid );
        }
        {
            auto invalid = "";
            auto res = ConfigParser::IsStringPair( invalid );
            REQUIRE( !res.IsValid );
        }
        {
            auto invalid = "hello     =\"world\"";
            auto res = ConfigParser::IsStringPair( invalid );
            REQUIRE( !res.IsValid );
        }
    }
}

TEST_CASE( "Float Key Pair Test", "[Float]" )
{
    SECTION( "Valid Float Pairs" )
    {
        {
            auto res = ConfigParser::IsFloatPair( "resolution=2.0f" );
            REQUIRE( res.IsValid );
        }
        {
            auto res = ConfigParser::IsFloatPair( "resolution=2f" );
            REQUIRE( res.IsValid );
        }
        {
            auto res = ConfigParser::IsFloatPair( "resolution=-2f" );
            REQUIRE( res.IsValid );
        }
        {
            auto res = ConfigParser::IsFloatPair( "resolution=+2f" );
            REQUIRE( res.IsValid );
        }
        {
            auto res = ConfigParser::IsFloatPair( "resolution=+2f" );
            REQUIRE( res.IsValid );
        }
    }

    SECTION( "INVALID Float Pairs" )
    {
        {
            auto res = ConfigParser::IsFloatPair( "resolution=z2.0f" );
            REQUIRE( !res.IsValid );
        }
        {
            auto res = ConfigParser::IsFloatPair( "=2f" );
            REQUIRE( !res.IsValid );
        }
        {
            auto res = ConfigParser::IsFloatPair( "#hey this is a comment" );
            REQUIRE( !res.IsValid );
        }
        {
            auto res = ConfigParser::IsFloatPair( "f" );
            REQUIRE( !res.IsValid );
        }
        {
            auto res = ConfigParser::IsFloatPair( "+2f" );
            REQUIRE( !res.IsValid );
        }
    }
}

TEST_CASE( "Int Key Pair Test", "[int]" )
{
    SECTION( "Valid Int Pairs" )
    {
        {
            auto res = ConfigParser::IsIntPair( "resolution=2" );
            REQUIRE( res.IsValid );
        }
        {
            auto res = ConfigParser::IsIntPair( "ers=+2" );
            REQUIRE( res.IsValid );
        }
        {
            auto res = ConfigParser::IsIntPair( "num=-2" );
            REQUIRE( res.IsValid );
        }
        {
            auto res = ConfigParser::IsIntPair( "reso=225961" );
            REQUIRE( res.IsValid );
        }
        {
            auto res = ConfigParser::IsIntPair( "reso=-225961" );
            REQUIRE( res.IsValid );
        }
    }

    SECTION( "INVALID Int Pairs" )
    {
        {
            auto res = ConfigParser::IsIntPair( "reso  =-   225961" );
            REQUIRE( !res.IsValid );
        }
        {
            auto res = ConfigParser::IsIntPair( "=-225961" );
            REQUIRE( !res.IsValid );
        }
        {
            auto res = ConfigParser::IsIntPair( "=-2259--61" );
            REQUIRE( !res.IsValid );
        }
    }
}