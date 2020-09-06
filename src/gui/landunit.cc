# include "landunit.hh"

LandUnit::LandUnit ( void )
   : VisualElement ()
{
}

LandUnit::~LandUnit ( void )
{
}

void LandUnit::setType ( const LandUnitType& pNewType )
{
   mLandUnitType = pNewType;
   return;
}

LandUnit::LandUnitType LandUnit::type ( void ) const
{
   return ( mLandUnitType );
}