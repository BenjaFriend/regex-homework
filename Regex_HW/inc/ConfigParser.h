#pragma once

#include "pch.h"
#include <fstream>
#include "SectionData.h"

class ConfigParser
{
    typedef std::unordered_map< std::string, SectionData > SectionMap;

public:

    ConfigParser( const std::string & aConfigFile );

private:

    void Init();

    /** The config file name */
    std::string ConfigFileName;

    /** A map of keys and their specific data containers */
    SectionMap ConfigData;
};