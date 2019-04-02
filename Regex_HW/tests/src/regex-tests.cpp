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
            std::string valid = "resolution=2.0f";
            auto res = ConfigParser::IsFloatPair( valid );
            REQUIRE( res.IsValid );
        }
        {
            std::string valid = "resolution=2f";
            auto res = ConfigParser::IsFloatPair( valid );
            REQUIRE( res.IsValid );
        }
        {
            std::string valid = "resolution=-2f";
            auto res = ConfigParser::IsFloatPair( valid );
            REQUIRE( res.IsValid );
        }
        {
            auto valid = "resolution=+2f";
            auto res = ConfigParser::IsFloatPair( valid );
            REQUIRE( res.IsValid );
        }
        {
            auto valid = "resolution=+2f";
            auto res = ConfigParser::IsFloatPair( valid );
            REQUIRE( res.IsValid );
        }
    }

    SECTION( "INVALID Float Pairs" )
    {
        {
            std::string valid = "resolution=z2.0f";
            auto res = ConfigParser::IsFloatPair( valid );
            REQUIRE( !res.IsValid );
        }
        {
            std::string valid = "=2f";
            auto res = ConfigParser::IsFloatPair( valid );
            REQUIRE( !res.IsValid );
        }
        {
            std::string valid = "#hey this is a comment";
            auto res = ConfigParser::IsFloatPair( valid );
            REQUIRE( !res.IsValid );
        }
        {
            auto valid = "f";
            auto res = ConfigParser::IsFloatPair( valid );
            REQUIRE( !res.IsValid );
        }
        {
            auto valid = "+2f";
            auto res = ConfigParser::IsFloatPair( valid );
            REQUIRE( !res.IsValid );
        }
    }
}