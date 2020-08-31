# ifndef TERRAIN_HH_
# define TERRAIN_HH_

# include "animatedsprite.hh"
# include "visualelement.hh"

class Terrain : public VisualElement
{
   public:
      enum class TerrainType
      {
         Sea = 0 ,
         Land
      };

      /**
       * Explicit default constructor.
       */
      explicit Terrain ( void );

      /**
       * Virtual destructor.
       */
      virtual ~Terrain ( void );      

      /**
       * Pure virtual member function used to draw the current figure in the screen, if needed.
       */
      virtual void draw ( void ) override;

      /**
       * Member function used to set the current view type.
       * 
       * @param[in] pNewPerspectiveView Perspective for the current view.
       */
      virtual void setPerspectiveView ( const PerspectiveView& pNewPerspectiveView ) override;

      /**
       * Member function used to set the required renderer for the game.
       * 
       * @param[in] pNewRenderer Renderer used to draw.
       */
      virtual void setRenderer ( SDL_Renderer* pNewRenderer ) override;

      /**
       * Member function used to update the scale factor of the image to draw.
       * 
       * @param[in] pNewScaleFactor New scale factor to apply.
       */
      virtual void setScaleFactor ( const unsigned int& pNewScaleFactor ) override;

      /**
       * Member function used to set the texture to use while drawing.
       * 
       * @param[in] pNewTexture New texture to use while drawing.
       */
      virtual void setTexture ( SDL_Texture* pNewTexture ) override;

      /**
       * Member function used to set the current terrain type.
       * 
       * @param[in] pNewType New type to set.
       */
      void setType ( const TerrainType& pNewType );

      /**
       * Member function used to return the current terrain type.
       * 
       * @returns Current terrain type.
       */
      virtual TerrainType type ( void ) const;

      /**
       * Virtual member function used to update the element accordingly to the passage of time.
       * 
       * @param[in] pTimeDelta Update the visual component according to the time passage.
       */
      virtual void updateTime ( const double& pTimeDelta ) override;

   protected:
      TerrainType mTerrainType; /**< Member function used to remember the kind of terrain found. */
      AnimatedSprite mSeaSprite; /**< Sprite used to draw the actual water. */
};

# endif