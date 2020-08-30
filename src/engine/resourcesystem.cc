# include "resourcesystem.hh"

# include <fstream>
# include <SDL.h>
# include <SDL_image.h>

ResourceSystem::ResourceSystem ( void )
   : SystemComponent ()
{
   mMapLayouts     = std::shared_ptr< std::vector< std::vector< std::vector< char > > > > ( new std::vector< std::vector< std::vector< char > > > () );
}

ResourceSystem::~ResourceSystem ( void )
{
   terminate ();
}

bool ResourceSystem::init ( void )
{
   if ( !loadResourceIndex () )
      return ( false );

   if ( !loadResourceFiles () )
      return ( false );

   if ( !loadMapsFile () )
      return ( false );

   return ( true );
}

bool ResourceSystem::loadMapsFile ( void )
{
   // Try to load the maps file. The file path should be "res/maps.lst"
   std::ifstream index_file;
   index_file.open ( "res/maps.lst" );

   if ( !index_file.is_open () )
      return ( false );

   // Now try to load its contents. The contents should be a series of lines. Something
   // like this:
   //
   //    COUNT
   //    W
   //    H
   //    L1
   //    L2
   //    ...
   std::string total_maps_count_string;
   std::getline ( index_file , total_maps_count_string );

   if ( !IsInteger ( total_maps_count_string ) )
      return ( false );

   int total_maps_count = FromString ( total_maps_count_string );
   mMapLayouts->clear ();

   for ( int i = 0; i < total_maps_count && !index_file.eof (); i++ )
   {
      std::string width_string;
      std::string height_string;
      std::getline ( index_file , width_string );
      std::getline ( index_file , height_string );

      if ( !IsInteger ( width_string )
           || !IsInteger ( height_string ) )
         return ( false );

      int width;
      int height;
      width  = FromString ( width_string );
      height = FromString ( height_string );
      std::vector< std::vector< char > > raw_map;
      std::string raw_line;

      for ( int j = 0; j < height; j++ )
      {
         std::getline ( index_file , raw_line );

         if ( raw_line.size () != width )
            return ( false );

         std::vector< char > line;
         
         for ( int k = 0; k < width; k++ )
            line.push_back ( raw_line[ k ] );

         raw_map.push_back ( line );
      }

      mMapLayouts->push_back ( raw_map );
   }

   index_file.close ();
   return ( true );
}

bool ResourceSystem::loadResourceIndex ( void )
{
   // Try to load the resource index file. The file path should be "res/index.lst"
   std::ifstream index_file;
   index_file.open ( "res/index.lst" );

   if ( !index_file.is_open () )
      return ( false );

   // Now try to load its contents. The contents should be a series of lines. Something
   // like this:
   //
   //    KEY
   //    PATH
   //    KEY
   //    PATH
   //    ...
   while ( !index_file.eof () )
   {
      std::string key;
      std::string path;

      std::getline ( index_file , key );
      std::getline ( index_file , path );

      if ( !key.empty ()
           && !path.empty () )
      {
         int index = FromString ( key );
         mResourceIndexVector.push_back ( static_cast< ResourceIndex > ( index ) );
         mResourceIndex[ static_cast< ResourceIndex > ( index ) ] = path;
      }
   }

   index_file.close ();

   // Did I loaded the required amount of indexes?
   if ( mResourceIndexVector.size () != static_cast< int > ( ResourceIndex::TotalIndexes ) )
       return ( false );

   return ( true );
}

bool ResourceSystem::loadResourceFiles ( void )
{
   std::size_t size;
   size = mResourceIndexVector.size ();

   for ( std::size_t i = 0; i < size; i++ )
   {
      SDL_Texture* texture = IMG_LoadTexture ( mRendererSystem->rootRenderer () ,
                                               mResourceIndex[ mResourceIndexVector[ i ] ].c_str () );

      if ( texture == nullptr )
         return ( false );

      mResourceTextures[ mResourceIndexVector[ i ] ] = texture;
   }

   return ( true );
}

std::shared_ptr< std::vector< std::vector< std::vector< char > > > > ResourceSystem::mapLayouts ( void )
{
   return ( mMapLayouts );
}

SDL_Texture* ResourceSystem::resourceTexture ( const ResourceIndex& pResourceIndex )
{
   return ( mResourceTextures[ pResourceIndex ] );
}

void ResourceSystem::setDebugSystem ( std::shared_ptr< DebugSystem > pDebugSystem )
{
   mDebugSystem = pDebugSystem;
   return;
}

void ResourceSystem::setRendererSystem ( std::shared_ptr< RenderSystem > pRendererSystem )
{
   mRendererSystem = pRendererSystem;
   return;
}

void ResourceSystem::terminate ( void )
{
   std::size_t size;
   size = mResourceIndexVector.size ();

   for ( std::size_t i = 0; i < size; i++ )
   {
      SDL_Texture* texture = mResourceTextures[ mResourceIndexVector[ i ] ];
      mResourceTextures[ mResourceIndexVector[ i ] ] = nullptr;
      SDL_DestroyTexture ( texture );
   }

   mResourceIndex.clear ();
   mResourceTextures.clear ();
   mResourceIndexVector.clear ();
   return;
}