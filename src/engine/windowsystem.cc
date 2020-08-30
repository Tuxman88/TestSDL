# include "windowsystem.hh"

WindowSystem::WindowSystem ( void )
   : SystemComponent () ,
     mSDLWindow ( nullptr )
{
}

WindowSystem::~WindowSystem ( void )
{
   terminate ();
}

bool WindowSystem::init ( void )
{
   mSDLWindow = SDL_CreateWindow ( "Test game", // window's title
                                   10 , 25 , // coordinates on the screen, in pixels, of the window's upper left corner
                                   800 , 600 , // window's length and height in pixels  
                                   SDL_WINDOW_OPENGL ); // An OpenGL controlled window.

   if ( mSDLWindow == nullptr )
      return ( false );

   SDL_SetRelativeMouseMode ( SDL_TRUE );
   return ( true );
}

SDL_Window* WindowSystem::rootWindow ( void )
{
   return ( mSDLWindow );
}

void WindowSystem::terminate ( void )
{
   if ( mSDLWindow != nullptr )
   {
      SDL_DestroyWindow ( mSDLWindow );
      mSDLWindow = nullptr;
   }

   return;
}