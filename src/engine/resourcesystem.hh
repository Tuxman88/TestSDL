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
         TerrainSeaClear = 1 ,
         TerrainSeaDark = 2 ,
         TerrainLandForest = 3 ,
         TerrainLandGrass = 4 ,
         TerrainLandSand = 5 ,
         TerrainLandSnow = 6 ,
         TerrainLandTech = 7 ,
         TerrainLandDirt = 8 ,
         ForestTree = 9 ,
         SnowTree = 10 ,
         TotalIndexes = 11
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
       * Member function used to return the maps used in this game.
       * 
       * @returns Shared pointer to maps used in game.
       */
      std::shared_ptr< std::vector< std::vector< std::vector< char > > > > mapLayouts ( void );

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
       * Private member function used to load the maps file.
       * 
       * @returns "true" if the file is loaded correctly, "false" if not.
       */
      bool loadMapsFile ( void );

      /**
       * Private member function used to load the resource file with the indexes and paths.
       * 
       * @returns "true" if the file is loaded correctly, "false" if not.
       */
      bool loadResourceIndex ( void );

      /**
       * Private member function used to load the resource files.
       * 
       * @returns "true" if the file is loaded correctly, "false" if not.
       */
      bool loadResourceFiles ( void );

   private:
      std::shared_ptr< DebugSystem >  mDebugSystem;    /**< Shared pointer to the debug system used. */
      std::shared_ptr< RenderSystem > mRendererSystem; /**< Shared pointer to the rendering system. */

      std::map< ResourceIndex , std::string >  mResourceIndex;    /**< Map of the resource indexes and their corresponding file paths. */
      std::map< ResourceIndex , SDL_Texture* > mResourceTextures; /**< Map of the resource indexes and the loaded textures generated from them. */

      std::vector< ResourceIndex > mResourceIndexVector; /**< Vector of the loaded resource indexes. */

      std::shared_ptr< std::vector< std::vector< std::vector< char > > > > mMapLayouts; /**< Vector of map layouts. Each map layout is a table, so, a vector (list of) of vector (height of each map) of vector (width of each map) */
};

# endif