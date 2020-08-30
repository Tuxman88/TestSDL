# include "terrain.hh"

Terrain::Terrain ( void )
   : VisualElement () ,
     mTerrainType ( TerrainType::Sea )
{
}

Terrain::~Terrain ( void )
{
}

void Terrain::setType ( const TerrainType& pNewType )
{
   mTerrainType = pNewType;
   return;
}

Terrain::TerrainType Terrain::type ( void ) const
{
   return ( mTerrainType );
}