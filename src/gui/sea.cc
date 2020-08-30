# include "sea.hh"

Sea::Sea ( void )
   : Terrain ()
{
   // Lets create the profile of the animations. I have two profiles basically: Top and isometric view.

   // Profile for top view.
   AnimatedSprite::AnimationRowSettings settings;
   settings.ClipSize.Height = 48;
   settings.ClipSize.Width = 48;
   settings.FramesInRow = 10;
   settings.FrameTime = 1000000 / 10; // Time for 10 frames per second.
   settings.LoopAnimation = true;
   settings.LoopDelay = 0;
   mSeaSprite.setAnimationSettings ( 0 , settings );

   // Profile for top view.
   settings.ClipSize.Height = 48;
   settings.ClipSize.Width = 96;
   settings.FramesInRow = 10;
   settings.FrameTime = 1000000 / 10; // Time for 10 frames per second.
   settings.LoopAnimation = true;
   settings.LoopDelay = 0;
   mSeaSprite.setAnimationSettings ( 1 , settings );
}

Sea::~Sea ( void )
{
}

void Sea::draw ( void )
{
   mSeaSprite.setPosition ( mPosition );
   mSeaSprite.draw ();
   return;
}

void Sea::setPerspectiveView ( const PerspectiveView& pNewPerspectiveView )
{
   mPerspectiveView = pNewPerspectiveView;
   mSeaSprite.setCurrentAnimationRow ( static_cast< unsigned int > ( mPerspectiveView ) );
   return;
}

void Sea::setRenderer ( SDL_Renderer* pNewRenderer )
{
   mSeaSprite.setRenderer ( pNewRenderer );
   return;
}

void Sea::setScaleFactor ( const unsigned int& pNewScaleFactor )
{
   mSeaSprite.setScaleFactor ( pNewScaleFactor );
   return;
}

void Sea::setTexture ( SDL_Texture* pNewTexture )
{
   mSeaSprite.setTexture ( pNewTexture );
   return;
}

void Sea::updateTime ( const double& pTimeDelta )
{
   mSeaSprite.updateTime ( pTimeDelta );
   return;
}