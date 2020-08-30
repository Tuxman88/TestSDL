# include "cursor.hh"

Cursor::Cursor ( void )
   : VisualElement () ,
     mCursorState ( CursorState::Normal )
{
   // Lets create the profile of the animations. For now, the 3 states of the cursor are animated the same. The image
   // resource contains 10 frames in 3 rows, each row has sprites of the same 16x16 pixels.
   AnimatedSprite::AnimationRowSettings settings;
   settings.ClipSize.Height = 16;
   settings.ClipSize.Width = 16;
   settings.FramesInRow = 10;
   settings.FrameTime = 1000000 / 10; // Time for 10 frames per second.
   settings.LoopAnimation = true;
   settings.LoopDelay = 1000000;
   mCursorSprite.setAnimationSettings ( 2 , settings ); // Since I haven't set config for rows 0 and 1, the animation will copy the settings for those unknown settings.
}

Cursor::~Cursor ( void )
{
}

void Cursor::draw ( void )
{
   mCursorSprite.setPosition ( mPosition );
   mCursorSprite.draw ();
   return;
}

void Cursor::setRenderer ( SDL_Renderer* pNewRenderer )
{
   mCursorSprite.setRenderer ( pNewRenderer );
   return;
}

void Cursor::setScaleFactor ( const unsigned int& pNewScaleFactor )
{
   mCursorSprite.setScaleFactor ( pNewScaleFactor );
   return;
}

void Cursor::setTexture ( SDL_Texture* pNewTexture )
{
   mCursorSprite.setTexture ( pNewTexture );
   return;
}

void Cursor::setState ( const CursorState& pNewCursorState )
{
   // This also affects the current animation row
   mCursorState = pNewCursorState;
   mCursorSprite.setCurrentAnimationRow ( static_cast< unsigned int > ( mCursorState ) );
   return;
}

void Cursor::updateTime ( const double& pTimeDelta )
{
   mCursorSprite.updateTime ( pTimeDelta );
   return;
}