# include "map.hh"

# include "sea.hh"

Map::Map ( void )
   : mRenderer ( nullptr )
{
}

Map::~Map ( void )
{
}

void Map::draw ( void )
{
   std::size_t vertical_size;
   std::size_t horizontal_size;
   vertical_size = mCurrentMap.size ();

   for ( std::size_t i = 0; i < vertical_size; i++ )
   {
      horizontal_size = mCurrentMap[ i ].size ();

      for ( std::size_t j = 0; j < horizontal_size; j++ )
      {
         Sea* sea;

         switch ( mCurrentMap[ i ][ j ]->type () )
         {
            case Terrain::TerrainType::Sea:
               sea = (Sea*)mCurrentMap[ i ][ j ];
               sea->draw ();
               break;
         }
      }
   }

   return;
}

void Map::setCurrentMap ( const unsigned int& pCurrentMap )
{
   std::size_t vertical_size;
   std::size_t horizontal_size;
   vertical_size = mCurrentMap.size ();

   for ( std::size_t i = 0; i < vertical_size; i++ )
   {
      horizontal_size = mCurrentMap[ i ].size ();

      for ( std::size_t j = 0; j < horizontal_size; j++ )
      {
         delete mCurrentMap[ i ][ j ];
         mCurrentMap[ i ][ j ] = nullptr;
      }
   }

   mCurrentMap.clear ();
   VisualElement::Position current_position;
   current_position.X = 0;
   current_position.Y = 0;

   // Iterate over the layout
   vertical_size = mMapLayouts->at ( pCurrentMap ).size ();
   horizontal_size = mMapLayouts->at ( pCurrentMap )[ 0 ].size ();
   
   for ( std::size_t i = 0; i < vertical_size; i++ )
   {
      std::vector< Terrain* > new_row;
      current_position.X = 0;

      for ( std::size_t j = 0; j < horizontal_size; j++ )
      {
         Terrain* new_terrain;
         new_terrain = nullptr;

         switch ( mMapLayouts->at ( pCurrentMap )[ i ][ j ] )
         {
            case 'c':
               new_terrain = new Sea ();
               new_terrain->setPosition ( current_position );
               new_terrain->setType ( Terrain::TerrainType::Sea );
               new_terrain->setRenderer ( mRenderer );
               new_terrain->setTexture ( mResourceSystem->resourceTexture ( ResourceSystem::ResourceIndex::TerrainSeaClear ) );
               break;
         }

         new_row.push_back ( new_terrain );
         current_position.X += 48;
      }

      mCurrentMap.push_back ( new_row );
      current_position.Y += 48;
   }

   return;
}

void Map::setMapLayouts ( std::shared_ptr< std::vector< std::vector< std::vector< char > > > > pMapLayouts )
{
   mMapLayouts = pMapLayouts;
   return;
}

void Map::setRenderer ( SDL_Renderer* pRendererSystem )
{
   mRenderer = pRendererSystem;
   return;
}

void Map::setResourceSystem ( std::shared_ptr< ResourceSystem > pResourceSystem )
{
   mResourceSystem = pResourceSystem;
   mMapLayouts = mResourceSystem->mapLayouts ();
   return;
}

void Map::updateTime ( const double& pTimeDelta )
{
   std::size_t vertical_size;
   std::size_t horizontal_size;
   vertical_size = mCurrentMap.size ();

   for ( std::size_t i = 0; i < vertical_size; i++ )
   {
      horizontal_size = mCurrentMap[ i ].size ();

      for ( std::size_t j = 0; j < horizontal_size; j++ )
         mCurrentMap[ i ][ j ]->updateTime ( pTimeDelta );
   }

   return;
}