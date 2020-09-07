# include "landunit.hh"

LandUnit::LandUnit ( void )
   : VisualElement () ,
     mLandUnitType ( LandUnitType::None )
{
}

LandUnit::~LandUnit ( void )
{
}

void LandUnit::move ( const int& pXDelta , 
                      const int& pYDelta )
{
   mMoveOffset.X += pXDelta;
   mMoveOffset.Y += pYDelta;
   return;
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