# include "cursor.hh"

Cursor::Cursor ( void )
   : AnimatedSprite ()
{
   setClipSize ( 16 , 16 );
}

Cursor::~Cursor ( void )
{
}

void Cursor::draw ( void )
{
   // The destination area corresponds to the final area to draw on, considering the scale factor
   SDL_Rect destination_area;
   destination_area.x = mPosition.X;
   destination_area.y = mPosition.Y;
   destination_area.w = mRenderSize.Width;
   destination_area.h = mRenderSize.Height;

   // The origin area from the texture
   SDL_Rect clip_area;
   clip_area.x = mClipSize.Width * mCurrentAnimationFrame;
   clip_area.y = mClipSize.Height * mCurrentAnimationRow;
   clip_area.w = mClipSize.Width;
   clip_area.h = mClipSize.Height;

   SDL_RenderCopy ( mRenderer , mTexture , &clip_area , &destination_area );

   return;
}

void Cursor::setState ( const CursorState& pNewCursorState )
{
   mCursorState = pNewCursorState;

   // This also affects the current animation row
   mCurrentAnimationRow = static_cast< unsigned int > ( mCursorState );

   if ( mCurrentAnimationRow > 2 )
      mCurrentAnimationRow = 2;

   return;
}

void Cursor::updateTime ( const double& pTimeDelta )
{
   mTimeAccumulator += pTimeDelta;

   // The cursor has 10 frames. One second has 1'000,000 microseconds.
   // So, a frame passes every 100,000 microseconds
   while ( mTimeAccumulator >= 100000 )
   {
      mCurrentAnimationFrame++;
      mTimeAccumulator -= 100000;

      if ( mCurrentAnimationFrame >= 10 )
         mCurrentAnimationFrame = 0;
   }

   return;
}