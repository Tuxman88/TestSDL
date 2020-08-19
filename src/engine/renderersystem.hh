# ifndef RENDERSYSTEM_HH_
# define RENDERSYSTEM_HH_

# include <memory>
# include "systemcomponent.hh"
# include "windowsystem.hh"

class RenderSystem : public SystemComponent
{
   public:
      /**
       * Explicit default constructor.
       */
      explicit RenderSystem ( void );

      /**
       * Virtual destructor.
       */
      virtual ~RenderSystem ( void );

      /**
       * Member function used to clear the current screen renderer.
       */
      void clearScreen ( void );

      /**
       * Virtual member function used to initialize the render system of the root window.
       * 
       * @returns "true" if the initialization succeeds, "false" otherwize.
       */
      virtual bool init ( void ) override;

      /**
       * Member function used to return a pointer to the root renderer of the SDL system.
       * 
       * @returns Pointer to the renderer used.
       */
      SDL_Renderer* rootRenderer ( void );

      /**
       * Member function used to set the reference to the WindowSystem of the game.
       * 
       * @param[in] pWindowSystem Shared pointer to the Window System instance.
       */
      void setWindowSystem ( std::shared_ptr< WindowSystem > pWindowSystem );

      /**
       * Virtual member function used to finish the execution of the render system.
       */
      virtual void terminate ( void ) override;

      /**
       * Member function used to send the current video frame to the screen.
       */
      void updateScreen ( void );

   private:
      SDL_Renderer* mSDLRenderer;

      std::shared_ptr< WindowSystem > mWindowSystem;
};

# endif