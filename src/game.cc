# include "game.hh"

# include <iostream>
# include <SDL.h>

Game::Game ( void )
   : SystemComponent () ,
	  mQuitGame ( false )
{
   mEngineSystem = std::shared_ptr< EngineSystem > ( new EngineSystem () );
}

Game::~Game ( void )
{
   terminate ();
}

void Game::drawGame ( void )
{
	mCursor->draw ();

	return;
}

bool Game::init ( void )
{
	mDebugSystem = mEngineSystem->debugSystem ();

	mDebugSystem->logToFile ( "Starting engine" );

	if ( !mEngineSystem->init () )
	{
		
		EngineSystem::InitStatus init_status;
		init_status = mEngineSystem->status ();

		switch ( init_status )
		{
			case EngineSystem::InitStatus::AllOk:
				mDebugSystem->logToFile ( "Failed: AllOK" );
				break;

			case EngineSystem::InitStatus::ErrorRendererInit:
				mDebugSystem->logToFile ( "Failed: ErrorRenderInit" );
				break;

			case EngineSystem::InitStatus::ErrorResourceInit:
				mDebugSystem->logToFile ( "Failed: ErrorResourceInit" );
				break;

			case EngineSystem::InitStatus::ErrorVideoInit:
				mDebugSystem->logToFile ( "Failed: ErrorVideoInit" );
				break;

			case EngineSystem::InitStatus::ErrorWindowInit:
				mDebugSystem->logToFile ( "Failed: ErrorWindowInit" );
				break;
		}

		mEngineSystem->terminate ();

		return ( false );
	}

	mDebugSystem->logToFile ( "Engine started" );
	mCursor = std::shared_ptr< Cursor > ( new Cursor () );
	mCursor->setRenderer ( mEngineSystem->rootRenderer () );
	mCursor->setTexture ( mEngineSystem->resource ( ResourceSystem::ResourceIndex::Cursor ) );
	mDebugSystem->logToFile ( "Game started" );

   return ( true );
}

void Game::processEvents ( std::shared_ptr< std::queue< SDL_Event > > pEventsToProcess )
{
	// Iterate over the current events of the system and see if we need to do something.
	while ( !pEventsToProcess->empty () )
	{
		SDL_Event sdl_event;
		sdl_event = pEventsToProcess->front ();
		pEventsToProcess->pop ();

		switch ( sdl_event.type )
		{
			case SDL_QUIT:
				mQuitGame = true;
				break;

			case SDL_WINDOWEVENT:
				// The user did something to the screen. What happened?
				switch ( sdl_event.window.event )
				{
					case SDL_WINDOWEVENT_SHOWN:
						// Window is now visible.
						break;

					case SDL_WINDOWEVENT_HIDDEN:
						// Window is now hidden. Not minimized, but covered.
						break;

					case SDL_WINDOWEVENT_MOVED:
						// User moved the window.
						break;

					case SDL_WINDOWEVENT_RESIZED:
						// User rezied the window.
						break;

					case SDL_WINDOWEVENT_MINIMIZED:
						// User minimized the window.
						break;

					case SDL_WINDOWEVENT_MAXIMIZED:
						// User maximized the window.
						break;

					case SDL_WINDOWEVENT_RESTORED:
						// User restored the window.
						break;

					case SDL_WINDOWEVENT_ENTER:
						// Window gained mouse focus.
						break;

					case SDL_WINDOWEVENT_LEAVE:
						// Window lost mouse focus.
						break;

					case SDL_WINDOWEVENT_FOCUS_GAINED:
						// Window gained keyboard focus.
						break;

					case SDL_WINDOWEVENT_FOCUS_LOST:
						// Window lost keyboard focus.
						break;
				}
				break;

			case SDL_KEYDOWN:
				// A key was pressed.
				break;

			case SDL_KEYUP:
				// A key was released.
				break;

			case SDL_MOUSEMOTION:
				// The mouse was moved over the screen.
				mCursor->setPosition ( sdl_event.motion.x ,
											  sdl_event.motion.y );
				break;

			case SDL_MOUSEBUTTONDOWN:
				// A mouse button was pressed.
				break;

			case SDL_MOUSEBUTTONUP:
				// A mouse button was released.
				break;

			case SDL_MOUSEWHEEL:
				// The mouse wheel was used.
				break;

			default:
				// Ignore event.
				break;
		}
	}

	return;
}

void Game::start ( void )
{
	while ( !mQuitGame )
	{
		processEvents ( mEngineSystem->readEvents () );
		mEngineSystem->cleanScreen ();
		drawGame ();
		mEngineSystem->updateScreen ();
	}

	return;
}

void Game::terminate ( void )
{
	mEngineSystem->terminate ();

   return;
}