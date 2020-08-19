# include "graphicelement.hh"

GraphicElement::GraphicElement ( void )
   : mRenderer ( nullptr) ,
     mTexture ( nullptr ) ,
     mTimeAccumulator ( 0 )
{
}

GraphicElement::~GraphicElement ( void )
{
}

GraphicElement::Position GraphicElement::position ( void ) const
{
   return ( mPosition );
}

int GraphicElement::positionX ( void ) const
{
   return ( mPosition.X );
}

int GraphicElement::positionY ( void ) const
{
   return ( mPosition.Y );
}

GraphicElement::Size GraphicElement::renderSize ( void ) const
{
   return ( mRenderSize );
}

void GraphicElement::setPosition ( const GraphicElement::Position& pNewPosition )
{
   mPosition = pNewPosition;

   return;
}

void GraphicElement::setPosition ( const int& pNewX ,
                                   const int& pNewY )
{
   mPosition.X = pNewX;
   mPosition.Y = pNewY;

   return;
}

void GraphicElement::setPositionX ( const int& pNewX )
{
   mPosition.X = pNewX;

   return;
}

void GraphicElement::setPositionY ( const int& pNewY )
{
   mPosition.Y = pNewY;

   return;
}

void GraphicElement::setRenderer ( SDL_Renderer* pNewRenderer )
{
   mRenderer = pNewRenderer;

   return;
}

void GraphicElement::setRenderSize ( const Size& pNewSize )
{
   mRenderSize = pNewSize;

   return;
}

void GraphicElement::setRenderSize ( const int& pNewWidth ,
                               const int& pNewHeight )
{
   mRenderSize.Width  = pNewWidth;
   mRenderSize.Height = pNewHeight;

   return;
}

void GraphicElement::setRenderSizeHeight ( const int& pNewHeight )
{
   mRenderSize.Height = pNewHeight;

   return;
}

void GraphicElement::setRenderSizeWidth ( const int& pNewWidth )
{
   mRenderSize.Width = pNewWidth;

   return;
}

void GraphicElement::setTexture ( SDL_Texture* pNewTexture )
{
   mTexture = pNewTexture;

   return;
}
