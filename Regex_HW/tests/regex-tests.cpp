#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch2/catch.hpp"

#include "pch.h"
#include <regex>
#include <string>

#include "ConfigParser.h"
#include "Section.h"
#include "SectionDataElement.h"

TEST_CASE( "Section Creation", "[Section]" )
{
    Section sec( "Sec Name Test", nullptr );

    REQUIRE( sec.GetName() == "Sec Name Test" );
    REQUIRE( sec.GetParent() == nullptr );
}

TEST_CASE( "Config Parser", "[Config]" )
{
    ConfigParser c;
   
    REQUIRE( c.GetSectionCount() == 0 );
}

/*
TEST_CASE( "Section Header", "[regex]" )
{
    auto res = ConfigParser::IsSectionHeader( "[header]" );
    REQUIRE( res.size() == 2 );
}*/