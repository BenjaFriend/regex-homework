#pragma once

#include "SectionDataElement.h"

typedef std::unordered_map< std::string, SectionDataElement > SectionMap;

class Section
{
public:

    Section() {}

    Section( const std::string & aName, Section* aParent = nullptr );

    ~Section();

    FORCE_INLINE void SetParent( class Section* aParent ) { ParentSection = aParent; }
    FORCE_INLINE Section* GetParent() const { return ParentSection; }
    FORCE_INLINE const std::string & GetName() const { return Name; }
    FORCE_INLINE SectionMap & GetData() { return Data; }

private:

    /** Pointer to the parent section of this */
    Section* ParentSection = nullptr;

    /** Name of this section */
    std::string Name;

    /** The data inside this section */
    SectionMap Data;
};
