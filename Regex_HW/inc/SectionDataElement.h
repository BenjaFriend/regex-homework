#pragma once

#include "pch.h"

/// <summary>
/// Section data is a way to store the data from the config
/// </summary>
/// <author>Ben Hoffman</author>
class SectionDataElement
{
public:

    SectionDataElement( const std::string & aKeyName )
        : KeyName( aKeyName )
    {

    }

    ~SectionDataElement() = default;

    FORCE_INLINE const std::string & GetKeyName() const { return KeyName; }
    FORCE_INLINE void SetKeyName( const std::string & aName ) { KeyName = aName; }

    void GetData( void* aOutData ) { /* #TODO Use a functor to get the data */ }

private:

    std::string KeyName;
    
    // Function Pointer to get he data
};