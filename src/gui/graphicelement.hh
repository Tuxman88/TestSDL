# ifndef GRAPHICELEMENT_HH_
# define GRAPHICELEMENT_HH_

# include <SDL.h>

class GraphicElement
{
   public:
      struct Position
      {
         Position ( void )
            : X ( 0 ) ,
              Y ( 0 )
         {
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

         int Height;
         int Width;
      };

      /**
       * Explicit default constructor.
       */
      explicit GraphicElement ( void );

      /**
       * Virtual destructor.
       */
      virtual ~GraphicElement ( void );

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
      void setRenderer ( SDL_Renderer* pNewRenderer );

      /**
       * Member function used to update the size of the visual component via a Size structure.
       * 
       * @param[in] pNewSize Size structure to update.
       */
      void setRenderSize ( const Size& pNewSize );

      /**
      * Member function used to update the size of the visual component via the individual components.
      * 
      * @param[in] pNewWidth  Width to set.
      * @param[in] pNewHeight Height to set.
      */
      void setRenderSize ( const int& pNewWidth ,
                           const int& pNewHeight );

      /**
      * Member function used to update the individual height component.
      * 
      * @param[in] pNewHeight New height of the component.
      */
      void setRenderSizeHeight ( const int& pNewHeight );

      /**
       * Member function used to update the individual width component.
       * 
       * @param[in] pNewWidth New width of the component.
       */
      void setRenderSizeWidth ( const int& pNewWidth );

      /**
       * Member function used to set the texture to use while drawing.
       * 
       * @param[in] pNewTexture New texture to use while drawing.
       */
      void setTexture ( SDL_Texture* pNewTexture );

      /**
       * Virtual member function used to update the element accordingly to the passage of time.
       * 
       * @param[in] pTimeDelta Update the visual component according to the time passage.
       */
      virtual void updateTime ( const double& pTimeDelta ) = 0;

   protected:
      Position mPosition; /**< Position of the graphic element. */

      Size mClipSize;   /**< Size of the area to clip from the texture. */
      Size mRenderSize; /**< Size of the graphic element to be displayed. */

      SDL_Renderer* mRenderer; /**< Pointer to the renderer used to draw the element on screen. */

      SDL_Texture* mTexture; /**< Pointer to the corresponding texture to use, if any. */

      double mTimeAccumulator;
};

# endif