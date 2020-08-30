# include "visualelement.hh"

VisualElement::VisualElement ( void )
   : mPerspectiveView ( PerspectiveView::TopView ) ,
     mRenderer ( nullptr) ,
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
      updateRenderValues ();
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
      updateRenderValues ();
   }

   return;
}

void VisualElement::setClipSizeHeight ( const unsigned int& pNewHeight )
{
   if ( pNewHeight > 0 )
   {
      mClipSize.Height = pNewHeight;
      updateRenderValues ();
   }

   return;
}

void VisualElement::setClipSizeWidth ( const unsigned int& pNewWidth )
{
   if ( pNewWidth > 0 )
   {
      mClipSize.Width = pNewWidth;
      updateRenderValues ();
   }

   return;
}

void VisualElement::setPerspectiveView ( const PerspectiveView& pNewPerspectiveView )
{
   mPerspectiveView = pNewPerspectiveView;
   return;
}

void VisualElement::setPosition ( const VisualElement::Position& pNewPosition )
{
   mPosition = pNewPosition;
   updateRenderValues ();
   return;
}

void VisualElement::setPosition ( const int& pNewX ,
                                  const int& pNewY )
{
   mPosition.X = pNewX;
   mPosition.Y = pNewY;
   updateRenderValues ();
   return;
}

void VisualElement::setPositionX ( const int& pNewX )
{
   mPosition.X = pNewX;
   updateRenderValues ();
   return;
}

void VisualElement::setPositionY ( const int& pNewY )
{
   mPosition.Y = pNewY;
   updateRenderValues ();
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
      updateRenderValues ();
   }

   return;
}

void VisualElement::setTexture ( SDL_Texture* pNewTexture )
{
   mTexture = pNewTexture;
   return;
}

void VisualElement::updateRenderValues ( void )
{
   mRenderPosition = mPosition.scaled ( mScaleFactor );
   mRenderSize     = mClipSize.scaled ( mScaleFactor );
   return;
}