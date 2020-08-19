# include "cursor.hh"

Cursor::Cursor ( void )
   : GraphicElement ()
{
   setSize ( 64 , 64 );
}

Cursor::~Cursor ( void )
{
}

void Cursor::draw ( void )
{
   SDL_Rect destination_area;
   destination_area.x = mPosition.X;
   destination_area.y = mPosition.Y;
   destination_area.w = mSize.Width;
   destination_area.h = mSize.Height;
   SDL_RenderCopy ( mRenderer , mTexture , nullptr , &destination_area );

   return;
}