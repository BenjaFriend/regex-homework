#pragma once

#include "SectionDataElement.h"

typedef std::unordered_map< std::string, ISectionData* > SectionDataMap;

class Section
{
public:

    Section() {}

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

    void ListData() const;

    template< typename T >
    void AddData( const std::string & aKey, T val )
    {
        if ( Data.find( aKey ) != Data.end() )
        {
            std::cerr << "Error: Key " << aKey << " already exists in section " << Name << std::endl;
            return;
        }
        ISectionData* data = new SectionDataElement<T>( aKey, val );
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
