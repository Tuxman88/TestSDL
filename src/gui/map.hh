# ifndef MAP_HH_
# define MAP_HH_

# include <map>
# include <SDL.h>

# include "../engine/resourcesystem.hh"
# include "terrain.hh"
# include "visualelement.hh"

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
       * Member function used to configure the new view of the map.
       * 
       * @param[in] pNewPerspectiveView New view style.
       */
      void setPerspectiveView ( const VisualElement::PerspectiveView& pNewPerspectiveView );

      /**
       * Member function used to set the renderer system for the screen.
       * 
       * @param[in] pRendererSystem Pointer to the renderer to use.
       */
      void setRenderer ( SDL_Renderer* pRendererSystem );

      /**
       * Member function used to set a resource used in the map.
       * 
       * @param[in] pResourceSystem Shared pointer to the resource system manager.
       */
      void setResourceSystem ( std::shared_ptr< ResourceSystem > pResourceSystem );

      /**
      * Member function used to update the element accordingly to the passage of time.
      * 
      * @param[in] pTimeDelta Update the visual component according to the time passage.
      */
      void updateTime ( const double& pTimeDelta );

   private:
      std::shared_ptr< ResourceSystem > mResourceSystem; /**< Shared pointer to the resource system. */

      std::shared_ptr< std::vector< std::vector< std::vector< char > > > > mMapLayouts; /**< Vector of map layouts to use. */

      std::vector< std::vector< Terrain* > > mCurrentMap; /**< Table with the current map terrain */

      SDL_Renderer* mRenderer; /**< Pointer to the renderer system. */

      VisualElement::PerspectiveView mPerspectiveView; /**< Type of view for the map. */
};

# endif