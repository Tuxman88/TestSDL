# ifndef RESOURCESYSTEM_HH_
# define RESOURCESYSTEM_HH_

# include <map>
# include <memory>
# include <string>
# include <vector>
# include "debugsystem.hh"
# include "renderersystem.hh"
# include "systemcomponent.hh"

class ResourceSystem : public SystemComponent
{
   public:
      enum class ResourceIndex
      {
         Cursor = 0 ,
         TotalIndexes = 1
      };

      /**
       * Explicit default constructor.
       */
      explicit ResourceSystem ( void );

      /**
       * Virtual destructor.
       */
      virtual ~ResourceSystem ( void );

      /**
       * Virtual member function used to initialize the resource system.
       */
      virtual bool init ( void ) override;

      /**
       * Member function used to return a pointer to a resource texture.
       *
       * @param[in] pResourceIndex Index of the resource required.
       * 
       * @returns Pointer to the SDL texture.
       */
      SDL_Texture* resourceTexture ( const ResourceIndex& pResourceIndex );

      /**
       * Member function used to set the debug system.
       * 
       * @param[in] pDebugSystem Debug system to use.
       */
      void setDebugSystem ( std::shared_ptr< DebugSystem > pDebugSystem );

      /**
       * Member function used to set the current renderer.
       * 
       * @param[in] pRendererSystem Renderer system.
       */
      void setRendererSystem ( std::shared_ptr< RenderSystem > pRendererSystem );

      /**
       * Virtual member function used to finish the operations of the resource system.
       */
      virtual void terminate ( void ) override;

   private:
      /**
       * Private member function used to load the resource file with the indexes and paths.
       */
      bool loadResourceIndex ( void );

      /**
       * Private member function used to load the resource files.
       */
      bool loadResourceFiles ( void );

   private:
      std::shared_ptr< DebugSystem >  mDebugSystem;
      std::shared_ptr< RenderSystem > mRendererSystem;

      std::map< ResourceIndex , std::string >  mResourceIndex;
      std::map< ResourceIndex , SDL_Texture* > mResourceTextures;

      std::vector< ResourceIndex > mResourceIndexVector;
};

# endif