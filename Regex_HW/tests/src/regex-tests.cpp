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
        auto res = ConfigParser::IsSectionHeader( "[header]" );
        REQUIRE( res.size() == 2 );

        res = ConfigParser::IsSectionHeader( "[header:subheader]" );
        REQUIRE( res.size() == 2 );

        res = ConfigParser::IsSectionHeader( "[header:subheader]    #  Comment time!" );
        REQUIRE( res.size() == 2 );

        res = ConfigParser::IsSectionHeader( "[header34]    #  Comment time!" );
        REQUIRE( res.size() == 2 );

        res = ConfigParser::IsSectionHeader( "[42]" );
        REQUIRE( res.size() == 2 );

        res = ConfigParser::IsSectionHeader( "[]" );
        REQUIRE( res.size() == 2 );
    }

    SECTION( "Invalid Headers" )
    {
        auto res = ConfigParser::IsSectionHeader( "header" );
        REQUIRE( res.size() == 0 );

        res = ConfigParser::IsSectionHeader( "# this is a comment!" );
        REQUIRE( res.size() == 0 );

        res = ConfigParser::IsSectionHeader( "42" );
        REQUIRE( res.size() == 0 );
    }
}

TEST_CASE( "String Key Pair", "[regex]" )
{
    SECTION( "Valid String Pairs" )
    {
        std::string valid = "resolution=\"1080x700\"";
        auto res = ConfigParser::IsStringPair( valid );
        REQUIRE( res.size() != 0 );

        valid = "chartype=\"blue tower\"";
        res = ConfigParser::IsStringPair( valid );
        REQUIRE( res.size() != 0 );

        valid = "chartype=\"blue tower 4242 z\"";
        res = ConfigParser::IsStringPair( valid );
        REQUIRE( res.size() != 0 );

        valid = "chartyp56_e=\"blue tower 4242 z\"";
        res = ConfigParser::IsStringPair( valid );
        REQUIRE( res.size() != 0 );
    }

    SECTION( "Invalid String Pairs" )
    {
        std::string invalid = "resolution=";
        auto res = ConfigParser::IsStringPair( invalid );
        REQUIRE( res.size() <= 2 );

        invalid = "=";
        res = ConfigParser::IsStringPair( invalid );
        REQUIRE( res.size() <= 2 );

        invalid = "";
        res = ConfigParser::IsStringPair( invalid );
        REQUIRE( res.size() <= 2 );

        invalid = "hello     =\"world\"";
        res = ConfigParser::IsStringPair( invalid );
        REQUIRE( res.size() <= 2 );
    }
}