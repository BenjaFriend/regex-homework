#include "pch.h"
#include "Section.h"

Section::Section( const std::string & aName, Section* aParent /* = nullptr */ )
    : Name( aName ), ParentSection( aParent )
{
}

Section::~Section()
{
    // Remove dangling pointers
    ParentSection = nullptr;

    // Delete the map of data
    for ( SectionMap::iterator itr = Data.begin(); itr != Data.end(); ++itr )  
        SAFE_DELETE( itr->second );
    
    Data.clear();
}