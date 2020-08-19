# include "cursor.hh"

Cursor::Cursor ( void )
   : AnimatedElement ()
{
   setRenderSize ( 16 , 16 );
   mClipSize = mRenderSize;
}

Cursor::~Cursor ( void )
{
}

void Cursor::draw ( void )
{
   SDL_Rect destination_area;
   destination_area.x = mPosition.X;
   destination_area.y = mPosition.Y;
   destination_area.w = mRenderSize.Width;
   destination_area.h = mRenderSize.Height;
   SDL_Rect clip_area;
   clip_area.x = mClipSize.Width * mCurrentFrame;
   clip_area.y = 0;
   clip_area.w = mClipSize.Width;
   clip_area.h = mClipSize.Height;

   SDL_RenderCopy ( mRenderer , mTexture , &clip_area , &destination_area );

   return;
}