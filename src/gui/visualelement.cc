# include "visualelement.hh"

VisualElement::VisualElement ( void )
   : mRenderer ( nullptr) ,
     mTexture ( nullptr ) ,
     mTimeAccumulator ( 0 ) ,
     mScaleFactor ( 1 )
{
   setScaleFactor ( 1 ); // Initialize this as a factor of 1
}

VisualElement::~VisualElement ( void )
{
}

VisualElement::Size VisualElement::clipSize ( void ) const
{
   return ( mClipSize );
}

VisualElement::Position VisualElement::position ( void ) const
{
   return ( mPosition );
}

int VisualElement::positionX ( void ) const
{
   return ( mPosition.X );
}

int VisualElement::positionY ( void ) const
{
   return ( mPosition.Y );
}

VisualElement::Size VisualElement::renderSize ( void ) const
{
   return ( mRenderSize );
}

unsigned int VisualElement::scaleFactor ( void ) const
{
   return ( mScaleFactor );
}

void VisualElement::setClipSize ( const Size& pNewClipSize )
{
   if ( pNewClipSize.Height > 0
        && pNewClipSize.Width > 0 )
   {
      mClipSize = pNewClipSize;
      updateRenderSize ();
   }

   return;
}

void VisualElement::setClipSize ( const unsigned int& pWidth ,
                                  const unsigned int& pHeight )
{
   if ( pWidth > 0 
        && pHeight > 0 )
   {
      mClipSize.Height = pHeight;
      mClipSize.Width = pWidth;
      updateRenderSize ();
   }

   return;
}

void VisualElement::setClipSizeHeight ( const unsigned int& pNewHeight )
{
   if ( pNewHeight > 0 )
   {
      mClipSize.Height = pNewHeight;
      updateRenderSize ();
   }

   return;
}

void VisualElement::setClipSizeWidth ( const unsigned int& pNewWidth )
{
   if ( pNewWidth > 0 )
   {
      mClipSize.Width = pNewWidth;
      updateRenderSize ();
   }

   return;
}

void VisualElement::setPosition ( const VisualElement::Position& pNewPosition )
{
   mPosition = pNewPosition;

   return;
}

void VisualElement::setPosition ( const int& pNewX ,
                                  const int& pNewY )
{
   mPosition.X = pNewX;
   mPosition.Y = pNewY;

   return;
}

void VisualElement::setPositionX ( const int& pNewX )
{
   mPosition.X = pNewX;

   return;
}

void VisualElement::setPositionY ( const int& pNewY )
{
   mPosition.Y = pNewY;

   return;
}

void VisualElement::setRenderer ( SDL_Renderer* pNewRenderer )
{
   mRenderer = pNewRenderer;

   return;
}

void VisualElement::setScaleFactor ( const unsigned int& pNewScaleFactor )
{
   if ( pNewScaleFactor >= 1 )
   {
      mScaleFactor = pNewScaleFactor;
      updateRenderSize ();
   }

   return;
}

void VisualElement::setTexture ( SDL_Texture* pNewTexture )
{
   mTexture = pNewTexture;

   return;
}

void VisualElement::updateRenderSize ( void )
{
   mRenderSize.Width  = mClipSize.Width  * mScaleFactor;
   mRenderSize.Height = mClipSize.Height * mScaleFactor;

   return;
}