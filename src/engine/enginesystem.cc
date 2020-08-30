# include "enginesystem.hh"

EngineSystem::EngineSystem ( void )
	: SystemComponent () ,
	  mInitStatus ( EngineSystem::InitStatus::NotStarted )
{
	mDebugSystem    = std::shared_ptr< DebugSystem >    ( new DebugSystem () );
	mVideoSystem    = std::shared_ptr< VideoSystem >    ( new VideoSystem () );
	mWindowSystem   = std::shared_ptr< WindowSystem >   ( new WindowSystem () );
	mRenderSystem   = std::shared_ptr< RenderSystem >   ( new RenderSystem () );
	mResourceSystem = std::shared_ptr< ResourceSystem > ( new ResourceSystem () );

	mDebugSystem->init ();
}

EngineSystem::~EngineSystem ( void )
{
	terminate ();
}

std::shared_ptr< DebugSystem > EngineSystem::debugSystem ( void )
{
	return ( mDebugSystem );
}

bool EngineSystem::init ( void )
{
	// Try to init the SDL Video System
	if ( !mVideoSystem->init () )
	{
		mInitStatus = InitStatus::ErrorVideoInit;
		return ( false );
	}

	// Try to init the Root Window
	if ( !mWindowSystem->init () )
	{
		mInitStatus = InitStatus::ErrorWindowInit;
		return ( false );
	}

	// Try to init the Renderer System
	mRenderSystem->setWindowSystem ( mWindowSystem );

	if ( !mRenderSystem->init () )
	{
		mInitStatus = InitStatus::ErrorRendererInit;
		return ( false );
	}

	// Try to init the Resource System
	mResourceSystem->setDebugSystem    ( mDebugSystem );
	mResourceSystem->setRendererSystem ( mRenderSystem );

	if ( !mResourceSystem->init () )
	{
		mInitStatus = InitStatus::ErrorResourceInit;
		return ( false );
	}

	mInitStatus = InitStatus::AllOk;
   return ( true );
}

void EngineSystem::cleanScreen ( void )
{
	mRenderSystem->clearScreen ();
	return;
}

std::shared_ptr< std::queue< SDL_Event > > EngineSystem::readEvents ( void )
{
	std::shared_ptr< std::queue< SDL_Event > > events_loaded;
	SDL_Event sdl_event;
	events_loaded = std::shared_ptr< std::queue< SDL_Event > > ( new std::queue< SDL_Event > () );

	while ( SDL_PollEvent ( &sdl_event ) )
		events_loaded->push ( sdl_event );

	return ( events_loaded );
}

SDL_Texture* EngineSystem::resource ( const ResourceSystem::ResourceIndex& pRequestedResourceIndex )
{
	return ( mResourceSystem->resourceTexture ( pRequestedResourceIndex ) );
}

std::shared_ptr< ResourceSystem > EngineSystem::resourceSystem ( void ) const
{
	return ( mResourceSystem );
}

SDL_Renderer* EngineSystem::rootRenderer ( void )
{
	return ( mRenderSystem->rootRenderer () );
}

EngineSystem::InitStatus EngineSystem::status ( void )
{
	return ( mInitStatus );
}

void EngineSystem::terminate ( void )
{
	mRenderSystem->terminate ();
	mWindowSystem->terminate ();
	mVideoSystem->terminate ();
	mDebugSystem->terminate ();
	return;
}

void EngineSystem::updateScreen ( void )
{
	mRenderSystem->updateScreen ();
	return;
}