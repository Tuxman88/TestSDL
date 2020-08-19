# include "videosystem.hh"

# include <SDL.h>

VideoSystem::VideoSystem ( void )
	: SystemComponent () ,
	  mSystemInitialized ( false )
{
}

VideoSystem::~VideoSystem ( void )
{
	terminate ();
}

bool VideoSystem::init ( void )
{
	if ( SDL_Init ( SDL_INIT_VIDEO ) )
	{
		return ( false );
	}

   return ( true );
}

void VideoSystem::terminate ( void )
{
	if ( mSystemInitialized )
	{
		mSystemInitialized = false;
		SDL_Quit ();
	}

	return;
}