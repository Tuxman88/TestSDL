# include "map.hh"

Map::Map ( void )
{
}

Map::~Map ( void )
{
}

void Map::draw ( void )
{
   return;
}

void Map::setCurrentMap ( const unsigned int& pCurrentMap )
{
   return;
}

void Map::setMapLayouts ( std::shared_ptr< std::vector< std::vector< std::vector< char > > > > pMapLayouts )
{
   mMapLayouts = pMapLayouts;

   return;
}

void Map::setResource ( const ResourceSystem::ResourceIndex& pResourceIndex ,
                        SDL_Texture* pResource )
{
   mResources[ pResourceIndex ] = pResource;

   return;
}

void Map::updateTime ( const double& pTimeDelta )
{
   return;
}