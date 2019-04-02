#pragma once

#include "pch.h"
#include <fstream>
#include "Section.h"
#include "Utils.h"

#define C_OK    1
#define C_FAIL  2

typedef std::unordered_map< std::string, Section >  SectionMap;

struct MatchRes
{
    MatchRes( bool aValid, std::smatch aMatchRes ) 
        : IsValid( aValid ), MatchResult( aMatchRes )
    { }

    const bool IsValid;
    std::smatch MatchResult;
};

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

    /// <summary>
    /// Get the data of this config
    /// </summary>
    /// <returns></returns>
    SectionMap & GetData() { return  ConfigData; }

    Section & operator []( const std::string aSecName ) 
    {
        return ConfigData [ aSecName ]; 
    }

    /// <summary>
    /// List all sections in the current config file
    /// </summary>
    void ListAllSections();

    /// <summary>
    /// Returns true if this source line is a section header
    /// </summary>
    /// <param name="aSource">The source string to check</param>
    /// <returns>A matchg group will be populated</returns>
    static const MatchRes IsSectionHeader( const std::string & aSource );

    /// <summary>
    /// Check if the given  string is a key value  pair
    /// with a string data type. 
    /// </summary>
    /// <param name="aSource">The source string to check</param>
    /// <returns>A match group will be populated if true</returns>
    static const MatchRes IsStringPair( const std::string & aSource );

    /// <summary>
    /// Check if the given  string is a key value  pair
    /// with a string data type. 
    /// </summary>
    /// <param name="aSource">The source string to check</param>
    /// <returns>A match group will be populated if true</returns>
    static const MatchRes IsIntPair( const std::string & aSource );

    /// <summary>
    /// Check if the given  string is a key value  pair
    /// with a string data type. 
    /// </summary>
    /// <param name="aSource">The source string to check</param>
    /// <returns>A match group will be populated if true</returns>
    static const MatchRes IsBoolPair( const std::string & aSource );

    /// <summary>
    /// Check if the given string is a float value pair
    /// </summary>
    /// <param name="aSource">Source string</param>
    /// <returns>A match group will be populated if true</returns>
    static const MatchRes IsFloatPair( const std::string & aSource );

private:

    void AddSection( const std::string & aSectionName );

    /** The config file name */
    std::string ConfigFileName;

    /** A map of sections to their map of data */
    SectionMap ConfigData;
};