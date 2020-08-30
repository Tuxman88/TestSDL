# ifndef ENGINESYSTEM_HH_
# define ENGINESYSTEM_HH_

# include <memory>
# include <queue>
# include "debugsystem.hh"
# include "renderersystem.hh"
# include "resourcesystem.hh"
# include "systemcomponent.hh"
# include "videosystem.hh"
# include "windowsystem.hh"

class EngineSystem : public SystemComponent
{
   public:
      enum class InitStatus
      {
         NotStarted ,
         AllOk ,
         ErrorRendererInit ,
         ErrorResourceInit ,
         ErrorVideoInit ,
         ErrorWindowInit         
      };

      /**
       * Explicit default constructor.
       */
      explicit EngineSystem ( void );

      /**
       * Virtual destructor.
       */
      virtual ~EngineSystem ( void );

      /**
       * Member function used to return a shared pointer to the debug system.
       * 
       * @return Shared pointer to the debug system.
       */
      std::shared_ptr< DebugSystem > debugSystem ( void );

      /**
       * Virtual member function used to initialize the game engine.
       * 
       * @returns "true" if the initialization succeeds, "false" if not.
       */
      virtual bool init ( void ) override;

      /**
       * Member function used to request the cleaning of the current window element.
       */
      void cleanScreen ( void );

      /**
       * Member function used to read and parce the events reported by SDL. The events are then converted into the known type.
       * 
       * @returns Queue with the events to consider. If no event is queued according to SDL, then this queue will be empty.
       */
      std::shared_ptr< std::queue< SDL_Event > > readEvents ( void );

      /**
       * Member function used to return a pointer to the resource index requested.
       * 
       * @returns Pointer to the resource requested.
       */
      SDL_Texture* resource ( const ResourceSystem::ResourceIndex& pRequestedResourceIndex );

      /**
       * Member function used to return a shared pointer to the resource system.
       * 
       * @returns Shared pointer to the resource system.
       */
      std::shared_ptr< ResourceSystem > resourceSystem ( void ) const;

      /**
      * Member function used to return a pointer to the root renderer of the SDL system.
      * 
      * @returns Pointer to the renderer used.
      */
      SDL_Renderer* rootRenderer ( void );

      /**
       * Member function used to initialize the overall rendering engine.
       */
      InitStatus status ( void );

      /**
       * Virtual member function used to finish the execution of the game engine.
       */
      virtual void terminate ( void ) override;

      /**
       * Member function used to send the current video buffer to the screen.
       */
      void updateScreen ( void );

   private:
      std::shared_ptr< DebugSystem >    mDebugSystem;    /**< Shared pointer to the debug system of the game. */
      std::shared_ptr< RenderSystem >   mRenderSystem;   /**< Shared pointer to the render system of the game. */
      std::shared_ptr< ResourceSystem > mResourceSystem; /**< Shared pointer to the resource system. */
      std::shared_ptr< VideoSystem >    mVideoSystem;    /**< Shared pointer to the video system of the game. */
      std::shared_ptr< WindowSystem >   mWindowSystem;   /**< Shared pointer to the window system of the game. */

      InitStatus mInitStatus; /**< Init status of the game. */
};

# endif