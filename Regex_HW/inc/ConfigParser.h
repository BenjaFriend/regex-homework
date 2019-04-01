#pragma once

#include "pch.h"
#include <fstream>
#include "Section.h"
#include "Utils.h"

#define C_OK    1   
#define C_FAIL  2

typedef std::unordered_map< std::string, Section > SectionMap;

class ConfigParser
{

public:

    ConfigParser();

    /// <summary>
    /// Specify the config file name
    /// </summary>
    /// <param name="aConfigFile"></param>
    ConfigParser( const std::string & aConfigFile );

    ~ConfigParser();

    /// <summary>
    /// Runs the config parser on the given config file
    /// </summary>
    /// <returns>1 if successful, else an error code</returns>
    size_t Run();

    const size_t GetSectionCount() const { return ConfigData.size(); }

    SectionMap & GetData() { return  ConfigData; }

    /// <summary>
    /// Returns true if this source line is a section header
    /// </summary>
    /// <param name="aSource">The source string to check</param>
    /// <returns>A matchg group will be populated</returns>
    static const std::smatch IsSectionHeader( const std::string & aSource );

    /// <summary>
    /// Check if the given  string is a key value  pair
    /// with a string data type. 
    /// </summary>
    /// <param name="aSource">The source string to check</param>
    /// <returns>A match group will be populated if true</returns>
    static const std::smatch IsStringPair( const std::string & aSource );

    /// <summary>
    /// Check if the given  string is a key value  pair
    /// with a string data type. 
    /// </summary>
    /// <param name="aSource">The source string to check</param>
    /// <returns>A match group will be populated if true</returns>
    static const std::smatch IsIntPair( const std::string & aSource );

    /// <summary>
    /// Check if the given  string is a key value  pair
    /// with a string data type. 
    /// </summary>
    /// <param name="aSource">The source string to check</param>
    /// <returns>A match group will be populated if true</returns>
    static const std::smatch IsBoolPair( const std::string & aSource );

    /// <summary>
    /// Check if the given string is a float value pair
    /// </summary>
    /// <param name="aSource">Source string</param>
    /// <returns>A match group will be populated if true</returns>
    static const std::smatch IsFloatPair( const std::string & aSource );

private:

    void AddSection( const std::string & aSectionName );

    /** The config file name */
    std::string ConfigFileName;

    /** A map of sections to their map of data */
    SectionMap ConfigData;
};