# ifndef SNOWTREE_HH_
# define SNOWTREE_HH_

# include "landunit.hh"

class SnowTree : public LandUnit
{
   public:
      /**
       * Explicit constructor.
       */
      explicit SnowTree ( void );

      /**
       * Virtual destructor.
       */
      virtual ~SnowTree ( void );

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
};

# endif
