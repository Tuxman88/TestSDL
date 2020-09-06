# ifndef MAP_HH_
# define MAP_HH_

# include <map>
# include <SDL.h>

# include "../engine/resourcesystem.hh"
# include "landunit.hh"
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
       * Member function used to decrease the current zoom level.
       */
      void decreaseZoom ( void );

      /**
       * Member function used to draw the current map in the screen, if needed.
       */
      void draw ( void );

      /**
       * Member function used to increase the current zoom level of the map.
       */
      void increaseZoom ( void );

      /**
       * Member function used to move the current map down.
       */
      void moveDown ( void );

      /**
       * Member function used to move the current map left.
       */
      void moveLeft ( void );

      /**
       * Member function used to move the current map right.
       */
      void moveRight ( void );

      /**
       * Member function used to move the current map up.
       */
      void moveUp ( void );

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

      /**
      * Member function used to update the current position of the map grid depending on the view type.
      */
      void switchViewType ( void );

   private:
      /**
       * Member function used to apply a specified move vector to the elements of the game.
       * 
       * @param[in] pDirectionX Horizontal direction of the movement.
       * @param[in] pDirectionY Vertical direction of the movement.
       */
      void applyMoveVector ( const unsigned int& pDirectionX ,
                             const unsigned int& pDirectionY );

      /**
       * Member function used to apply the view type of the map.
       */
      void applyViewType ( void );

      /**
       * Member function used to apply the calculated zoom level.
       */
      void applyZoom ( void );

      /**
       * Member function used to remove the current map, if any.
       */
      void deleteMap ( void );

      /**
       * Member function used to scan the map and populate it with units as needed.
       */
      void populateMapUnits ( void );

      /**
       * Member function used to populate trees in the are specified by the offset.
       * 
       * @param[in] pOffsetX Horizontal offset of the area to populate
       * @param[in] pOffsetY Vertical offet of the area to populate.
       */
      void populateTrees ( const std::size_t& pOffsetX ,
                           const std::size_t& pOffsetY );

   private:
      std::shared_ptr< ResourceSystem > mResourceSystem; /**< Shared pointer to the resource system. */

      std::shared_ptr< std::vector< std::vector< std::vector< char > > > > mMapLayouts; /**< Vector of map layouts to use. */

      std::vector< std::vector< Terrain* > > mCurrentMap; /**< Table with the current map terrain */

      std::vector< LandUnit* > mLandUnits; /**< Vector of pointers to the land units. */

      SDL_Renderer* mRenderer; /**< Pointer to the renderer system. */

      VisualElement::PerspectiveView mPerspectiveView; /**< Type of view for the map. */

      unsigned int mCurrentMapIndex; /**< Current map index of those in the layouts. */
      unsigned int mZoomLevel;       /**< Current zoom level used to display the map. */
};

# endif