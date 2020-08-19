# ifndef GAME_HH_
# define GAME_HH_

# include <memory>
# include <SDL.h>
# include "engine/enginesystem.hh"
# include "engine/systemcomponent.hh"
# include "gui/cursor.hh"

class Game : public SystemComponent
{
   public:
      /**
       * Explicit default constructor.
       */
      explicit Game ( void );

      /**
       * Virtual destructor.
       */
      virtual ~Game ( void );

      /**
       * Virtual member function used to initialize the game.
       */
      virtual bool init ( void ) override;

      /**
       * Member function used to start the main loop of the game.
       */
      void start ( void );

      /**
       * Virtual member function used to terminate the execution of the game.
       */
      virtual void terminate ( void ) override;

   private:
      /**
       * Member function used to draw the game components after they have been positioned accordingly.
       */
      void drawGame ( void );

      /**
       * Private member function used to consume the system events reported by SDL.
       * 
       * @param[in] pEventsToProcess Queue of events to process.
       */
      void processEvents ( std::shared_ptr< std::queue< SDL_Event > > pEventsToProcess );

   private:
      std::shared_ptr< DebugSystem >  mDebugSystem;  /**< Shared pointer to the debug system. */
      std::shared_ptr< EngineSystem > mEngineSystem; /**< Shared pointer to the engine system. */
      std::shared_ptr< Cursor >       mCursor;       /**< Shared pointer to the cursor of the game. */

      bool mQuitGame; /**< Flag used to stop the game. */
};

# endif