# include "foresttree.hh"

ForestTree::ForestTree ( void )
   : LandUnit ()
{
   // Lets create the profile of the animations. I have two profiles basically: Top and isometric view.

   // Profile for top view.
   AnimatedSprite::AnimationRowSettings settings;
   settings.ClipSize.Height = 16;
   settings.ClipSize.Width = 16;
   settings.FramesInRow = 10;
   settings.FrameTime = 1000000 / 10; // Time for 10 frames per second.
   settings.LoopAnimation = true;
   settings.LoopDelay = 0;
   mUnitSprite.setAnimationSettings ( 0 , settings );

   // Profile for top view.
   settings.ClipSize.Height = 16;
   settings.ClipSize.Width = 16;
   settings.FramesInRow = 10;
   settings.FrameTime = 1000000 / 10; // Time for 10 frames per second.
   settings.LoopAnimation = true;
   settings.LoopDelay = 0;
   mUnitSprite.setAnimationSettings ( 1 , settings );
}

ForestTree::~ForestTree ( void )
{
}

void ForestTree::draw ( void )
{
   VisualElement::Position converted_position;

   if ( mPerspectiveView == VisualElement::PerspectiveView::TopView )
   {
      converted_position = mPosition;
      converted_position.X += mMoveOffset.X;
      converted_position.Y += mMoveOffset.Y;
      mUnitSprite.setPosition ( converted_position );
   }
   else
   {
      // Lets make some magic
      VisualElement::Position converted_position;
      converted_position.X = mPosition.X - mPosition.Y;
      converted_position.Y = ( mPosition.Y / 2 ) + ( mPosition.X / 2 );
      converted_position.X += mMoveOffset.X;
      converted_position.Y += mMoveOffset.Y;
      mUnitSprite.setPosition ( converted_position );
   }

   mUnitSprite.draw ();
   return;
}

void ForestTree::setPerspectiveView ( const PerspectiveView& pNewPerspectiveView )
{
   mPerspectiveView = pNewPerspectiveView;
   mUnitSprite.setCurrentAnimationRow ( static_cast< unsigned int > ( mPerspectiveView ) );
   mMoveOffset.X = 0;
   mMoveOffset.Y = 0;
   return;
}

void ForestTree::setRenderer ( SDL_Renderer* pNewRenderer )
{
   mUnitSprite.setRenderer ( pNewRenderer );
   return;
}

void ForestTree::setScaleFactor ( const unsigned int& pNewScaleFactor )
{
   mUnitSprite.setScaleFactor ( pNewScaleFactor );
   return;
}

void ForestTree::setTexture ( SDL_Texture* pNewTexture )
{
   mUnitSprite.setTexture ( pNewTexture );
   return;
}

void ForestTree::updateTime ( const double& pTimeDelta )
{
   mUnitSprite.updateTime ( pTimeDelta );
   return;
}