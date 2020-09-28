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
	mMap->draw ();
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

	// Initialize the cursor of the game
	mCursor = std::shared_ptr< Cursor > ( new Cursor () );
	mCursor->setRenderer ( mEngineSystem->rootRenderer () );
	mCursor->setTexture ( mEngineSystem->resource ( ResourceSystem::ResourceIndex::Cursor ) );

	// Initialize the map
	mMap = std::shared_ptr< Map > ( new Map () );
	mMap->setRenderer ( mEngineSystem->rootRenderer () );
	mMap->setResourceSystem ( mEngineSystem->resourceSystem () );
	mMap->setCurrentMap ( 0 );
	mMap->setPerspectiveView ( VisualElement::PerspectiveView::IsometricView );
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
				switch ( sdl_event.key.keysym.sym )
				{
					case SDLK_DOWN:
						mMap->moveUp ();
						break;

					case SDLK_ESCAPE:
						mQuitGame = true;
						break;

					case SDLK_KP_MINUS:
						mMap->decreaseZoom ();
						break;

					case SDLK_KP_PLUS:
						mMap->increaseZoom ();
						break;

					case SDLK_LEFT:
						mMap->moveRight ();
						break;

					case SDLK_RIGHT:
						mMap->moveLeft ();
						break;

					case SDLK_UP:
						mMap->moveDown ();
						break;

					case SDLK_v:
						mMap->switchViewType ();
						break;
				}
				break;

			case SDL_KEYUP:
				// A key was released.
				break;

			case SDL_MOUSEMOTION:
				// The X position is equal from the last mouse position?
				if ( sdl_event.motion.x == mCursor->positionX () )
				{
					// The mouse X position hasn't moved, but... does the user want to move the cursor to the left?
					if ( sdl_event.motion.xrel < 0 )
						// Mouse scroll to the left
						mMap->moveRight ();
					else if ( sdl_event.motion.xrel > 0 )
						// Mouse scroll to the right
						mMap->moveLeft ();
				}

				// The Y position is equal from the last mouse position?
				if ( sdl_event.motion.y == mCursor->positionY () )
				{
					// The mouse Y position hasn't moved, but... does the user want to move the cursor to the top?
					if ( sdl_event.motion.yrel < 0 )
						// Mouse scroll to the top
						mMap->moveDown ();
					else if ( sdl_event.motion.yrel > 0 )
						// Mouse scroll to the bottom
						mMap->moveUp ();
				}
				
				// The mouse was moved over the screen.
				mCursor->setPosition ( sdl_event.motion.x ,
											  sdl_event.motion.y );
											  
				break;

			case SDL_MOUSEBUTTONDOWN:
				// A mouse button was pressed.
				mCursor->setState ( Cursor::CursorState::Click );
				break;

			case SDL_MOUSEBUTTONUP:
				// A mouse button was released.
				mCursor->setState ( Cursor::CursorState::Normal );
				break;

			case SDL_MOUSEWHEEL:
				// The mouse wheel was used.
				if ( sdl_event.wheel.y > 0 )
					mMap->increaseZoom ();
				else if ( sdl_event.wheel.y < 0 )
					mMap->decreaseZoom ();

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
		updateGame ( current_cycle_time_delta );

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

void Game::updateGame ( const double& pTimeDelta )
{
	mCursor->updateTime ( pTimeDelta );
	mMap->updateTime ( pTimeDelta );
	return;
}