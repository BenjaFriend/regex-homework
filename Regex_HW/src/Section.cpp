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
    for ( SectionDataMap::iterator itr = Data.begin(); itr != Data.end(); ++itr )  
        SAFE_DELETE( itr->second );
    
    Data.clear();
}

void Section::ListData() const 
{
    std::cout << "Listing Data in [" << Name << "] " << std::endl;
    for ( const auto & dataMember : Data )
    {
        std::cout << "\t" << dataMember.first << " = ";
        dataMember.second->ListData();
        std::cout << std::endl;
    }
}