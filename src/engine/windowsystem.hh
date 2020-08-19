# ifndef WINDOWSYSTEM_HH_
# define WINDOWSYSTEM_HH_

# include <memory>
# include <SDL.h>
# include "systemcomponent.hh"

class WindowSystem : public SystemComponent
{
   public:
      /**
       * Explicit default constructor.
       */
      explicit WindowSystem ( void );

      /**
       * Virtual destructor.
       */
      virtual ~WindowSystem ( void );

      /**
       * Virtual member function used to initialize the SDL window.
       * 
       * @returns "true" if the initialization succeeds, "false" otherwize.
       */
      virtual bool init ( void ) override;

      /**
       * Member function used to return a shared pointer to the root window of the application.
       * 
       * @returns Pointer of the root window. The pointer should be validated for initialization.
       */
      SDL_Window* rootWindow ( void );

      /**
       * Virtual member function used to finish the usage of the SDL Window component.
       */
      virtual void terminate ( void ) override;

   private:
      SDL_Window* mSDLWindow;
};

# endif