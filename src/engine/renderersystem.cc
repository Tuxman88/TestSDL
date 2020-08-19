# include "renderersystem.hh"

RenderSystem::RenderSystem ( void )
   : SystemComponent () ,
     mSDLRenderer ( nullptr )
{
}

RenderSystem::~RenderSystem ( void )
{
   terminate ();
}

void RenderSystem::clearScreen ( void )
{
   // Set the render color
   SDL_SetRenderDrawColor ( mSDLRenderer , 
                            255 , // Red
                            255 , // Green
                            255 , // Blue
                            255 ); // Alpha

   // Clean the renderer
   SDL_RenderClear ( mSDLRenderer );

   return;
}

bool RenderSystem::init ( void )
{
   mSDLRenderer = SDL_CreateRenderer ( mWindowSystem->rootWindow () , // The renderer requires to be specified which window should render to
                                       -1 , // The driver index. -1 sets the first driver that kind of works
                                       //SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC ); // We need a hardware accelerated drawing and vsync
                                       SDL_RENDERER_ACCELERATED ); // We need a hardware accelerated drawing and vsync

   if ( mSDLRenderer == nullptr )
   {
      return ( false );
   }

   return ( true );
}

SDL_Renderer* RenderSystem::rootRenderer ( void )
{
   return ( mSDLRenderer );
}

void RenderSystem::setWindowSystem ( std::shared_ptr< WindowSystem > pWindowSystem )
{
   mWindowSystem = pWindowSystem;

   return;
}

void RenderSystem::terminate ( void )
{
   if ( mSDLRenderer != nullptr )
   {
      SDL_DestroyRenderer ( mSDLRenderer );
      mSDLRenderer = nullptr;
   }

   return;
}

void RenderSystem::updateScreen ( void )
{
   SDL_RenderPresent ( mSDLRenderer );

   return;
}