# ifndef MAP_HH_
# define MAP_HH_

# include <map>
# include <SDL.h>

# include "../engine/resourcesystem.hh"

class Map
{
   public:
      /**
       * Explicit default constructor.
       */
      explicit Map ( void );

      /**
       * Virtual destructor.
       */
      virtual ~Map ( void );

      /**
       * Member function used to draw the current map in the screen, if needed.
       */
      void draw ( void );

      /**
       * Member function used to set the current map layout to use.
       * 
       * @param[in] pMapIndex Map index to use for the current map.
       */
      void setCurrentMap ( const unsigned int& pMapIndex );

      /**
       * Member function used to set the current map layouts available.
       * 
       * @param[in] pMapLayouts Vector of map layouts to consider and manage.
       */
      void setMapLayouts ( std::shared_ptr< std::vector< std::vector< std::vector< char > > > > pMapLayouts );

      /**
       * Member function used to set a resource used in the map.
       * 
       * @param[in] pResourceIndex Index of the resource provided.
       * @param[in] pResource Pointer to the resource required.
       */
      void setResource ( const ResourceSystem::ResourceIndex& pResourceIndex ,
                         SDL_Texture* pResource );

      /**
      * Member function used to update the element accordingly to the passage of time.
      * 
      * @param[in] pTimeDelta Update the visual component according to the time passage.
      */
      void updateTime ( const double& pTimeDelta );

   private:
      std::map< ResourceSystem::ResourceIndex , SDL_Texture* > mResources; /**< Index of resources to manage. */

      std::shared_ptr< std::vector< std::vector< std::vector< char > > > > mMapLayouts; /**< Vector of map layouts to use. */
};

# endif