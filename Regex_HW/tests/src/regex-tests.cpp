#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch2/catch.hpp"

#include "pch.h"
#include <regex>
#include <string>

#include "ConfigParser.h"

TEST_CASE( "Section Header", "[regex]" )
{
    auto res = ConfigParser::IsSectionHeader( "[header]" );
    REQUIRE( res.size() == 2 );
}