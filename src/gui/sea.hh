# ifndef SEA_HH_
# define SEA_HH_

# include "terrain.hh"
# include "animatedsprite.hh"

class Sea : public Terrain
{
   public:
      /**
       * Explicit default constructor.
       */
      explicit Sea ( void );

      /**
       * Virtual destructor.
       */
      virtual ~Sea ( void );

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
       * Virtual member function used to update the element accordingly to the passage of time.
       * 
       * @param[in] pTimeDelta Update the visual component according to the time passage.
       */
      virtual void updateTime ( const double& pTimeDelta ) override;

   protected:
      AnimatedSprite mSeaSprite; /**< Sprite used to draw the actual water. */
};

# endif