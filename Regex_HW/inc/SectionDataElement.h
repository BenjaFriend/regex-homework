#pragma once

#include "pch.h"

/// <summary>
/// Section data is a way to store the data from the config
/// </summary>
/// <author>Ben Hoffman</author>
class ISectionData
{
public:

    ISectionData( const std::string & aKeyName )
        : KeyName( aKeyName )
    {
    }

    virtual ~ISectionData() {};

    FORCE_INLINE const std::string & GetKeyName() const { return KeyName; }
    FORCE_INLINE void SetKeyName( const std::string & aName ) { KeyName = aName; }

    virtual void GetData( void* aOutData ) {}

    virtual void ListData()
    {
        std::cout << "NULL" << std::endl;
    }

protected:

    std::string KeyName;
};

template<class T>
class SectionDataElement : public ISectionData
{
public:

    SectionDataElement( const std::string & aKeyName, T aData ) 
        : ISectionData( aKeyName ), MyData ( aData )
    {

    }

    virtual ~SectionDataElement()
    {

    }

    virtual void ListData() override
    {
        std::cout << MyData;
    }

    virtual void GetData( void* aOutData ) override
    {
        assert( aOutData != nullptr );
        T* out = static_cast< T* > ( aOutData );
        *out = MyData;
    }

    T MyData;
};