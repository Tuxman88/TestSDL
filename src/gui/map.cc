# include "map.hh"

Map::Map ( void )
   : mRenderer ( nullptr ) ,
     mPerspectiveView ( VisualElement::PerspectiveView::TopView ) ,
     mZoomLevel ( 1 )
{
}

Map::~Map ( void )
{
}

void Map::applyViewType ( void )
{
   std::size_t vertical_size;
   std::size_t horizontal_size;
   VisualElement::Position current_position;
   vertical_size = mCurrentMap.size ();

   if ( vertical_size )
      horizontal_size = mCurrentMap[ 0 ].size ();

   if ( mPerspectiveView == VisualElement::PerspectiveView::TopView )
   {
      // Iterate over the layout. In the case of the top view, the position of the elements is simple. This is just a grid:
      //
      //    ----------------
      //    |    |    |    |
      //    |    |    |    |
      //    ----------------
      //    |    |    |    |
      //    |    |    |    |
      //    ----------------
      //    |    |    |    |
      //    |    |    |    |
      //    ----------------
      current_position.X = 0;
      current_position.Y = 0;

      for ( std::size_t i = 0; i < vertical_size; i++ )
      {
         current_position.X = 0;

         for ( std::size_t j = 0; j < horizontal_size; j++ )
         {
            mCurrentMap[ i ][ j ]->setPosition ( current_position );
            current_position.X += 48;
         }

         current_position.Y += 48;
      }
   }
   else
   {
      // Iterate over the layout. In the case of the isometric view, we need to position stuff in diagonal.
      // Here, the top left cell of the map can't be in the corner of the map because the cell is in romboid form.
      //
      //    ----------------
      //    |      /\      |
      //    |   /      \   |
      //    |/            \|
      //    |\            /|
      //    |   \      /   |
      //    |      \/      |
      //    ----------------

      current_position.X = -48;
      current_position.Y = 0;

      VisualElement::Position local_position;
      local_position = current_position;

      for ( std::size_t i = 0; i < vertical_size; i++ )
      {
         for ( std::size_t j = 0; j < horizontal_size; j++ )
         {
            mCurrentMap[ i ][ j ]->setPosition ( current_position );
            current_position.X += 48;
            current_position.Y += 24;
         }

         local_position.Y += 24;
         local_position.X -= 48;
         current_position = local_position;
      }
   }

   return;
}

void Map::decreaseZoom ( void )
{
   mZoomLevel--;

   if ( mZoomLevel == 0 )
      mZoomLevel = 1;

   std::size_t vertical_size;
   std::size_t horizontal_size;
   vertical_size = mCurrentMap.size ();

   for ( std::size_t i = 0; i < vertical_size; i++ )
   {
      horizontal_size = mCurrentMap[ i ].size ();

      for ( std::size_t j = 0; j < horizontal_size; j++ )
         mCurrentMap[ i ][ j ]->setScaleFactor ( mZoomLevel );
   }

   return;
}

void Map::draw ( void )
{
   std::size_t vertical_size;
   std::size_t horizontal_size;
   vertical_size = mCurrentMap.size ();
   Terrain* terrain;

   for ( std::size_t i = 0; i < vertical_size; i++ )
   {
      horizontal_size = mCurrentMap[ i ].size ();

      for ( std::size_t j = 0; j < horizontal_size; j++ )
      {
         terrain = (Terrain*)mCurrentMap[ i ][ j ];
         terrain->draw ();
      }
   }

   return;
}

void Map::increaseZoom ( void )
{
   mZoomLevel++;

   if ( mZoomLevel > 10 )
      mZoomLevel = 10;
   
   std::size_t vertical_size;
   std::size_t horizontal_size;
   vertical_size = mCurrentMap.size ();

   for ( std::size_t i = 0; i < vertical_size; i++ )
   {
      horizontal_size = mCurrentMap[ i ].size ();

      for ( std::size_t j = 0; j < horizontal_size; j++ )
         mCurrentMap[ i ][ j ]->setScaleFactor ( mZoomLevel );
   }

   return;
}

void Map::moveDown ( void )
{
   std::size_t vertical_size;
   std::size_t horizontal_size;
   vertical_size = mCurrentMap.size ();
   Terrain* terrain;

   for ( std::size_t i = 0; i < vertical_size; i++ )
   {
      horizontal_size = mCurrentMap[ i ].size ();

      for ( std::size_t j = 0; j < horizontal_size; j++ )
      {
         terrain = (Terrain*)mCurrentMap[ i ][ j ];
         terrain->move ( 0 , 5 );
      }
   }

   return;
}

void Map::moveLeft ( void )
{
   std::size_t vertical_size;
   std::size_t horizontal_size;
   vertical_size = mCurrentMap.size ();
   Terrain* terrain;

   for ( std::size_t i = 0; i < vertical_size; i++ )
   {
      horizontal_size = mCurrentMap[ i ].size ();

      for ( std::size_t j = 0; j < horizontal_size; j++ )
      {
         terrain = (Terrain*)mCurrentMap[ i ][ j ];
         terrain->move ( -5 , 0 );
      }
   }

   return;
}

void Map::moveRight ( void )
{
   std::size_t vertical_size;
   std::size_t horizontal_size;
   vertical_size = mCurrentMap.size ();
   Terrain* terrain;

   for ( std::size_t i = 0; i < vertical_size; i++ )
   {
      horizontal_size = mCurrentMap[ i ].size ();

      for ( std::size_t j = 0; j < horizontal_size; j++ )
      {
         terrain = (Terrain*)mCurrentMap[ i ][ j ];
         terrain->move ( 5 , 0 );
      }
   }

   return;
}

void Map::moveUp ( void )
{
   std::size_t vertical_size;
   std::size_t horizontal_size;
   vertical_size = mCurrentMap.size ();
   Terrain* terrain;

   for ( std::size_t i = 0; i < vertical_size; i++ )
   {
      horizontal_size = mCurrentMap[ i ].size ();

      for ( std::size_t j = 0; j < horizontal_size; j++ )
      {
         terrain = (Terrain*)mCurrentMap[ i ][ j ];
         terrain->move ( 0 , -5 );
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
         new_terrain = new Terrain ();
         new_terrain->setPosition ( current_position );
         new_terrain->setRenderer ( mRenderer );

         switch ( mMapLayouts->at ( pCurrentMap )[ i ][ j ] )
         {
            case 'c':
               new_terrain->setType ( Terrain::TerrainType::Sea );
               new_terrain->setTexture ( mResourceSystem->resourceTexture ( ResourceSystem::ResourceIndex::TerrainSeaClear ) );
               break;

            case 'd':
               new_terrain->setType ( Terrain::TerrainType::Sea );
               new_terrain->setTexture ( mResourceSystem->resourceTexture ( ResourceSystem::ResourceIndex::TerrainSeaDark ) );
               break;

            case 's':
               new_terrain->setType ( Terrain::TerrainType::Land );
               new_terrain->setTexture ( mResourceSystem->resourceTexture ( ResourceSystem::ResourceIndex::TerrainLandSand ) );
               break;

            case 't':
               new_terrain->setType ( Terrain::TerrainType::Land );
               new_terrain->setTexture ( mResourceSystem->resourceTexture ( ResourceSystem::ResourceIndex::TerrainLandTech ) );
               break;

            case 'g':
               new_terrain->setType ( Terrain::TerrainType::Land );
               new_terrain->setTexture ( mResourceSystem->resourceTexture ( ResourceSystem::ResourceIndex::TerrainLandGrass ) );
               break;

            case 'f':
               new_terrain->setType ( Terrain::TerrainType::Land );
               new_terrain->setTexture ( mResourceSystem->resourceTexture ( ResourceSystem::ResourceIndex::TerrainLandForest ) );
               break;

            case 'n':
               new_terrain->setType ( Terrain::TerrainType::Land );
               new_terrain->setTexture ( mResourceSystem->resourceTexture ( ResourceSystem::ResourceIndex::TerrainLandSnow ) );
               break;
         }

         new_row.push_back ( new_terrain );
         current_position.X += 48;
      }

      mCurrentMap.push_back ( new_row );
      current_position.Y += 48;
   }

   applyViewType ();

   return;
}

void Map::setPerspectiveView ( const VisualElement::PerspectiveView& pNewPerspectiveView )
{
   mPerspectiveView = pNewPerspectiveView;
   std::size_t vertical_size;
   std::size_t horizontal_size;
   Terrain* terrain;
   vertical_size = mCurrentMap.size ();

   for ( std::size_t i = 0; i < vertical_size; i++ )
   {
      horizontal_size = mCurrentMap[ i ].size ();

      for ( std::size_t j = 0; j < horizontal_size; j++ )
      {
         terrain = (Terrain*)mCurrentMap[ i ][ j ];
         terrain->setPerspectiveView ( pNewPerspectiveView ); 
      }
   }

   applyViewType ();

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

void Map::switchViewType ( void )
{
   if ( mPerspectiveView == VisualElement::PerspectiveView::TopView )
      setPerspectiveView ( VisualElement::PerspectiveView::IsometricView );
   else
      setPerspectiveView ( VisualElement::PerspectiveView::TopView );

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