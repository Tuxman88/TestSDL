# include "resourcesystem.hh"

# include <fstream>
# include <SDL.h>
# include <SDL_image.h>

ResourceSystem::ResourceSystem ( void )
   : SystemComponent ()
{
}

ResourceSystem::~ResourceSystem ( void )
{
   terminate ();
}

bool ResourceSystem::init ( void )
{
   if ( !loadResourceIndex () )
   {
      return ( false );
   }

   if ( !loadResourceFiles () )
   {
      return ( false );
   }

   return ( true );
}

bool ResourceSystem::loadResourceIndex ( void )
{
   // Try to load the resource index file. The file path should be "res/index.lst"
   std::ifstream index_file;
   index_file.open ( "res/index.lst" );

   if ( !index_file.is_open () )
   {
      return ( false );
   }

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
   {
       return ( false );
   }

   return ( true );
}

bool ResourceSystem::loadResourceFiles ( void )
{
   int size;
   size = static_cast< int > ( mResourceIndexVector.size () );

   for ( int i = 0; i < size; i++ )
   {
      SDL_Texture* texture = IMG_LoadTexture ( mRendererSystem->rootRenderer () ,
                                               mResourceIndex[ mResourceIndexVector[ i ] ].c_str () );

      if ( texture == nullptr )
      {
         return ( false );
      }

      mResourceTextures[ mResourceIndexVector[ i ] ] = texture;
   }

   return ( true );
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
   int size;
   size = static_cast< int > ( mResourceIndexVector.size () );

   for ( int i = 0; i < size; i++ )
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