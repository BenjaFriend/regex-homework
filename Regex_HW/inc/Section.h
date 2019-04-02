#pragma once

#include "SectionDataElement.h"

typedef std::unordered_map< std::string, ISectionData* > SectionDataMap;

class Section
{
public:

    Section() {}

    /// <summary>
    /// Create a section given the name and a pointer to it's parent
    /// </summary>
    /// <param name="aName">Name of this section</param>
    /// <param name="aParent">Pointer to this section's parent [ nullptr by default ]</param>
    Section( const std::string & aName, Section* aParent = nullptr );

    ~Section();

    ISectionData & operator []( const std::string aKeyName )
    {
        return *Data [ aKeyName ];
    }

    FORCE_INLINE void SetParent( class Section* aParent ) { ParentSection = aParent; }
    FORCE_INLINE Section* GetParent() const { return ParentSection; }
    FORCE_INLINE const std::string & GetName() const { return Name; }
    FORCE_INLINE SectionDataMap & GetData() { return Data; }
    FORCE_INLINE const bool IsSubsection() const { return ParentSection != nullptr; }

    /// <summary>
    /// List the data that exists in this section to the console
    /// </summary>
    void ListData() const;

    /// <summary>
    /// Add data to this section at the given key
    /// </summary>
    /// <param name="aKey">The key to set data in</param>
    /// <param name="val">The data to set</param>
    template< typename T >
    void AddData( const std::string & aKey, T val )
    {
        if ( Data.find( aKey ) != Data.end() )
        {
            std::cerr << "Error: Key " << aKey << " already exists in section " << Name << std::endl;
            return;
        }
        ISectionData* data = new SectionDataElement< T >( aKey, val );
        Data [ aKey ] = data;
    }

private:

    /** Pointer to the parent section of this */
    Section* ParentSection = nullptr;

    /** Name of this section */
    std::string Name;

    /** The data inside this section */
    SectionDataMap Data;
};
