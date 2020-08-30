# ifndef VISUALELEMENT_HH_
# define VISUALELEMENT_HH_

# include <SDL.h>

class VisualElement
{
   public:
      struct Position
      {
         Position ( void )
            : X ( 0 ) ,
              Y ( 0 )
         {
         }

         Position scaled ( const unsigned int& pScaleValue )
         {
            Position temporal;
            temporal.X = X * pScaleValue;
            temporal.Y = Y * pScaleValue;
            return ( temporal );
         }

         int X;
         int Y;
      };

      struct Size
      {
         Size ( void )
            : Height ( 1 ) ,
              Width ( 1 )
         {
         }

         Size scaled ( const unsigned int& pScaleValue )
         {
            Size temporal;
            temporal.Width  = Width  * pScaleValue;
            temporal.Height = Height * pScaleValue;
            return ( temporal );
         }

         unsigned int Height;
         unsigned int Width;
      };

      enum class PerspectiveView
      {
         TopView = 0 ,
         IsometricView         
      };

      /**
       * Explicit default constructor.
       */
      explicit VisualElement ( void );

      /**
       * Virtual destructor.
       */
      virtual ~VisualElement ( void );

      /**
       * Member function used to return the current component size;
       * 
       * @returns Size of the visual component.
       */
      Size clipSize ( void ) const;

      /**
       * Pure virtual member function used to draw the current figure in the screen, if needed.
       */
      virtual void draw ( void ) = 0;

      /**
       * Member function used to return the current position of the graphic element.
       * 
       * @returns Position of the element.
       */
      Position position ( void ) const;

      /**
       * Member function used to return the current X coordinate of the graphic element.
       * 
       * @returns X coordinate of the graphic element.
       */
      int positionX ( void ) const;

      /**
      * Member function used to return the current Y coordinate of the graphic element.
      * 
      * @returns Y coordinate of the graphic element.
      */
      int positionY ( void ) const;

      /**
       * Member function used to return the current component size;
       * 
       * @returns Size of the visual component.
       */
      Size renderSize ( void ) const;

      /**
       * Member function used to return the current scale factor applied to this element.
       * 
       * @returns Unsigned int value that represents the scale factor applied to the visual element when drawn.
       */
      unsigned int scaleFactor ( void ) const;

      /**
       * Member function used to set the current clip size.
       * 
       * @param[in] pNewClipSize New clip size to use.
       */
      void setClipSize ( const Size& pNewClipSize );

      /**
       * Member function used to set the current clip size.
       * 
       * @param[in] pWidth New width of the clip size.
       * @param[in] pHeight New height of the clip size.
       */
      void setClipSize ( const unsigned int& pWidth ,
                         const unsigned int& pHeight );

      /**
       * Member function used to set the current clip size.
       * 
       * @param[in] pNewClipSize New clip size to use.
       */
      void setClipSizeHeight ( const unsigned int& pNewHeight );

      /**
       * Member function used to set the current clip size.
       * 
       * @param[in] pNewClipSize New clip size to use.
       */
      void setClipSizeWidth ( const unsigned int& pNewWidth );

      /**
       * Member function used to set the current view type.
       * 
       * @param[in] pNewPerspectiveView Perspective for the current view.
       */
      virtual void setPerspectiveView ( const PerspectiveView& pNewPerspectiveView );

      /**
       * Member function used to set the position of the visual component via a position structure.
       * 
       * @param[in] pNewPosition New position components.
       */
      void setPosition ( const Position& pNewPosition );

      /**
       * Member function used to set the position of the visual component via individual position values.
       * 
       * @param[in] pNewX X coordinate to update.
       * @param[in] pNewY Y coordinate to update.
       */
      void setPosition ( const int& pNewX ,
                         const int& pNewY );

      /**
       * Member function used to set the individual X position coordinate.
       * 
       * @param[in] pNewX X coordinate to update.
       */
      void setPositionX ( const int& pNewX );

      /**
      * Member function used to set the individual Y position coordinate.
      * 
      * @param[in] pNewY Y coordinate to update.
      */
      void setPositionY ( const int& pNewY );

      /**
       * Member function used to set the required renderer for the game.
       * 
       * @param[in] pNewRenderer Renderer used to draw.
       */
      virtual void setRenderer ( SDL_Renderer* pNewRenderer );

      /**
       * Member function used to update the scale factor of the image to draw.
       * 
       * @param[in] pNewScaleFactor New scale factor to apply.
       */
      virtual void setScaleFactor ( const unsigned int& pNewScaleFactor );

      /**
       * Member function used to set the texture to use while drawing.
       * 
       * @param[in] pNewTexture New texture to use while drawing.
       */
      virtual void setTexture ( SDL_Texture* pNewTexture );

      /**
       * Virtual member function used to update the element accordingly to the passage of time.
       * 
       * @param[in] pTimeDelta Update the visual component according to the time passage.
       */
      virtual void updateTime ( const double& pTimeDelta ) = 0;

   protected:
      /**
       * Member function used to update the render size after a change in the scale factor.
       */
      void updateRenderValues ( void );

   protected:
      Position mPosition; /**< Position of the graphic element before scaling. */
      Position mRenderPosition; /**< Position of the graphic element after scaling. */

      Size mClipSize;   /**< Size of the area to clip from the texture. */
      Size mRenderSize; /**< Size of the graphic element to be displayed. */

      PerspectiveView mPerspectiveView; /**< Perspective for the current view. */

      SDL_Renderer* mRenderer; /**< Pointer to the renderer used to draw the element on screen. */

      SDL_Texture* mTexture; /**< Pointer to the corresponding texture to use, if any. */

      double mTimeAccumulator; /**< Accumulator of time passed for any time-related calculation. */

      unsigned int mScaleFactor; /**< Scale factor to apply to the clip size to get a render size. */
};

# endif