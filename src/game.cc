# include "game.hh"

# include <chrono>
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
	auto last_system_time = std::chrono::high_resolution_clock::now ();
	double current_system_time_delta = 0;
	double frame_time_accumulator = 0;
	double frame_rate_time_accumulator = 0;
	int frame_counter = 0;

	while ( !mQuitGame )
	{
		// Process logic of the game.
		processEvents ( mEngineSystem->readEvents () );

		// How much time has passed?
		auto current_system_time = std::chrono::high_resolution_clock::now ();
		double current_cycle_time_delta = std::chrono::duration< double , std::micro > ( current_system_time - last_system_time ).count ();

		// Set the last system time as the current system time
		last_system_time = current_system_time;

		// Update my accumulators related to the frame time and frame rate calculator accumulator.
		frame_time_accumulator += current_cycle_time_delta;
		frame_rate_time_accumulator += current_cycle_time_delta;

		if ( frame_rate_time_accumulator >= 1000000 )
		{
			mDebugSystem->logToFile ( "FPS: " + ToString< int > ( frame_counter ) );
			frame_counter = 0;
			frame_rate_time_accumulator -= 1000000;
		}

		// A certain amount of microseconds have passed. Check if there have been enough microseconds
		// to require drawing the game.
		//
		// 1 frame = 16 milliseconds
		// 1 millisecond = 1000 microseconds
		// 1 frame = 16000 microseconds.
		if ( frame_time_accumulator >= 16000 )
		{
			frame_counter++;
			frame_time_accumulator -= 16000;
			mEngineSystem->cleanScreen ();
			drawGame ();
			mEngineSystem->updateScreen ();
		}
	}

	return;
}

void Game::terminate ( void )
{
	mEngineSystem->terminate ();

   return;
}