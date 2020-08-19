# include "graphicelement.hh"

GraphicElement::GraphicElement ( void )
   : mRenderer ( nullptr) ,
     mTexture ( nullptr )
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

void GraphicElement::setSize ( const Size& pNewSize )
{
   mSize = pNewSize;

   return;
}

void GraphicElement::setSize ( const int& pNewWidth ,
                               const int& pNewHeight )
{
   mSize.Width  = pNewWidth;
   mSize.Height = pNewHeight;

   return;
}

void GraphicElement::setSizeHeight ( const int& pNewHeight )
{
   mSize.Height = pNewHeight;

   return;
}

void GraphicElement::setSizeWidth ( const int& pNewWidth )
{
   mSize.Width = pNewWidth;

   return;
}

void GraphicElement::setTexture ( SDL_Texture* pNewTexture )
{
   mTexture = pNewTexture;

   return;
}

GraphicElement::Size GraphicElement::size ( void ) const
{
   return ( mSize );
}