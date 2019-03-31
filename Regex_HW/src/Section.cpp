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
}