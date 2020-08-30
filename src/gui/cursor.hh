# ifndef CURSOR_HH_
# define CURSOR_HH_

# include "animatedsprite.hh"
# include "visualelement.hh"

class Cursor : public VisualElement
{
   public:
      enum class CursorState
      {
         Normal = 0 ,
         Hover = 1 ,
         Click = 2
      };

      /**
       * Explicit default constructor.
       */
      explicit Cursor ( void );

      /**
       * Virtual destructor.
       */
      virtual ~Cursor ( void );

      /**
       * Virtual member function used to draw the current cursor according to the configuration set.
       */
      virtual void draw ( void ) override;

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
       * Member function used to set the current cursor state.
       * 
       * @param[in] pNewCursorState New cursor state to set.
       */
      void setState ( const CursorState& pNewCursorState );

      /**
       * Member function used to update the current time delta of the frame.
       * 
       * @param[in] pTimeDelta Time difference in current time.
       */
      virtual void updateTime ( const double& pTimeDelta ) override;

   private:
      CursorState mCursorState; /**< Current cursor state, which also affects the current animation. */
      AnimatedSprite mCursorSprite; /**< Cursor sprite to use, which should be animated. */
};

# endif