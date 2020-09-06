# include "map.hh"

# include <algorithm>
# include <cstdlib>

# include "foresttree.hh"

Map::Map ( void )
   : mRenderer ( nullptr ) ,
     mPerspectiveView ( VisualElement::PerspectiveView::TopView ) ,
     mCurrentMapIndex ( 0 ) ,
     mZoomLevel ( 1 )
{
}

Map::~Map ( void )
{
   deleteMap ();
}

void Map::applyMoveVector ( const unsigned int& pDirectionX ,
                            const unsigned int& pDirectionY )
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
         terrain->move ( pDirectionX , pDirectionY );
      }
   }

   std::size_t size;
   size = mLandUnits.size ();
   ForestTree* forest_tree;

   for ( std::size_t i = 0; i < size; i++ )
      switch ( mLandUnits[ i ]->type () )
      {
         case LandUnit::LandUnitType::ForestTree:
            forest_tree = (ForestTree*)mLandUnits[ i ];
            forest_tree->move ( pDirectionX , pDirectionY );
            break;
      }

   return;
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

void Map::applyZoom ( void )
{
   std::size_t vertical_size;
   std::size_t horizontal_size;
   vertical_size = mCurrentMap.size ();

   for ( std::size_t i = 0; i < vertical_size; i++ )
   {
      horizontal_size = mCurrentMap[ i ].size ();

      for ( std::size_t j = 0; j < horizontal_size; j++ )
         mCurrentMap[ i ][ j ]->setScaleFactor ( mZoomLevel );
   }

   std::size_t size;
   size = mLandUnits.size ();

   for ( std::size_t i = 0; i < size; i++ )
      mLandUnits[ i ]->setScaleFactor ( mZoomLevel );

   return;
}

void Map::decreaseZoom ( void )
{
   mZoomLevel--;

   if ( mZoomLevel == 0 )
      mZoomLevel = 1;

   applyZoom ();

   return;
}

void Map::deleteMap ( void )
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

   std::size_t size;
   size = mLandUnits.size ();
   ForestTree* forest_tree;

   for ( std::size_t i = 0; i < size; i++ )
      switch ( mLandUnits[ i ]->type () )
      {
         case LandUnit::LandUnitType::ForestTree:
            forest_tree = (ForestTree*)mLandUnits[ i ];
            forest_tree->draw ();
            break;
      }

   return;
}

void Map::increaseZoom ( void )
{
   mZoomLevel++;

   if ( mZoomLevel > 10 )
      mZoomLevel = 10;
   
   applyZoom ();

   return;
}

void Map::moveDown ( void )
{
   applyMoveVector ( 0 , 5 );
   return;
}

void Map::moveLeft ( void )
{
   applyMoveVector ( -5 , 0 );
   return;
}

void Map::moveRight ( void )
{
   applyMoveVector ( 5 , 0 );
   return;
}

void Map::moveUp ( void )
{
   applyMoveVector ( 0 , -5 );
   return;
}

void Map::populateMapUnits ( void )
{
   // Iterate over the map and see which kind of terrain do we have here
   std::size_t vertical_size;
   std::size_t horizontal_size;
   vertical_size = mMapLayouts->at ( mCurrentMapIndex ).size ();

   for ( std::size_t i = 0; i < vertical_size; i++ )
   {
      horizontal_size = mMapLayouts->at ( mCurrentMapIndex )[ i ].size ();

      for ( std::size_t j = 0; j < horizontal_size; j++ )
      {
         switch ( mMapLayouts->at ( mCurrentMapIndex )[ i ][ j ] )
         {
            case 'f':
               populateTrees ( j , i );
               break;
         }
      }
   }

   // Sort the units, so they are drawn in the correct order, from top to bottom, left to right (reading order).
   sort ( mLandUnits.begin () , mLandUnits.end () , []( LandUnit* pLandUnitLeft , LandUnit* pLandUnitRight )
                                                    { 
                                                       unsigned int x1 , x2 , y1 , y2;
                                                       x1 = pLandUnitLeft->positionX ();
                                                       y1 = pLandUnitLeft->positionY ();
                                                       x2 = pLandUnitRight->positionX ();
                                                       y2 = pLandUnitRight->positionY ();

                                                       // If I'm higher than the other, then yes, I go first.
                                                       if ( y1 < y2 )
                                                         return ( true );

                                                       // If I'm lower than the other, then no, I go later
                                                       if ( y1 > y2 )
                                                         return ( false );

                                                       // Same height, order based on X
                                                       if ( x1 < x2 )
                                                          return ( true );
                                                       
                                                       return ( false );
                                                    } );

   return;
}

void Map::populateTrees ( const std::size_t& pOffsetX ,
                          const std::size_t& pOffsetY )
{
   // The offsets provided corresponds to the coordinates to start on.
   
   // Lets generate 10 trees per area
   for ( unsigned int i = 0; i < 50; i++ )
   {
      std::size_t random_x = rand () % 48;
      std::size_t random_y = rand () % 48;

      ForestTree* tree = new ForestTree ();
      tree->setType ( LandUnit::LandUnitType::ForestTree );
      tree->setTexture ( mResourceSystem->resourceTexture ( ResourceSystem::ResourceIndex::ForestTree ) );
      tree->setRenderer ( mRenderer );
      tree->setPosition ( static_cast< unsigned int > ( random_x + ( pOffsetX * 48 ) ), 
                          static_cast< unsigned int > ( random_y + ( pOffsetY * 48 ) ) );
      mLandUnits.push_back ( tree );
   }

   return;
}

void Map::setCurrentMap ( const unsigned int& pCurrentMap )
{
   deleteMap ();
   VisualElement::Position current_position;
   current_position.X = 0;
   current_position.Y = 0;
   mCurrentMapIndex = pCurrentMap;

   // Iterate over the layout
   std::size_t vertical_size = mMapLayouts->at ( pCurrentMap ).size ();
   std::size_t horizontal_size = mMapLayouts->at ( pCurrentMap )[ 0 ].size ();
   
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

            case 'r':
               new_terrain->setType ( Terrain::TerrainType::Land );
               new_terrain->setTexture ( mResourceSystem->resourceTexture ( ResourceSystem::ResourceIndex::TerrainLandDirt ) );
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

   populateMapUnits ();
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

   std::size_t size;
   size = mLandUnits.size ();

   for ( std::size_t i = 0; i < size; i++ )
      mLandUnits[ i ]->setPerspectiveView ( mPerspectiveView );

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

   std::size_t size;
   size = mLandUnits.size ();

   for ( std::size_t i = 0; i < size; i++ )
   {
      mLandUnits[ i ]->updateTime ( pTimeDelta );
   }

   return;
}