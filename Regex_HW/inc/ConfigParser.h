#pragma once

#include "pch.h"
#include <fstream>
#include "Section.h"


class ConfigParser
{

public:

    ConfigParser( const std::string & aConfigFile );

private:

    void Init();

    void AddSection( const std::string & aSectionName );

    /** The config file name */
    std::string ConfigFileName;

    /** A map of sections to their map of data */
    std::unordered_map< std::string, Section >  ConfigData;
};