# include "animatedsprite.hh"

AnimatedSprite::AnimatedSprite ( void )
   : VisualElement () ,
     mCurrentAnimationFrame ( 0 ) ,
     mCurrentAnimationRow ( 0 )
{
}

AnimatedSprite::~AnimatedSprite ( void )
{
}

AnimatedSprite::AnimationStatus AnimatedSprite::currentAnimationStatus ( void ) const
{
   return ( mAnimationRowStatus.at ( mCurrentAnimationRow ) );
}

unsigned int AnimatedSprite::currentAnimationRow ( void ) const
{
   return ( mCurrentAnimationRow );
}

void AnimatedSprite::draw ( void )
{
   // The destination area corresponds to the final area to draw on, considering the scale factor
   SDL_Rect destination_area;
   destination_area.x = mRenderPosition.X;
   destination_area.y = mRenderPosition.Y;
   // The size of the destination area depends on the current animation row settings, because some rows correspond to sizes
   // bigger or smaller.
   Size final_size = mAnimationRowSettings[ mCurrentAnimationRow ].ClipSize.scaled ( mScaleFactor );
   destination_area.w = final_size.Width;
   destination_area.h = final_size.Height;

   // The origin area from the texture
   // The first part is to calculate the final Y position of the upper left of the row considering that we might not be in the initial row anymore.
   SDL_Rect clip_area;
   clip_area.y = 0;

   for ( unsigned int i = 0; i < mCurrentAnimationRow; i++ )
      clip_area.y += mAnimationRowSettings[ i ].ClipSize.Height;

   clip_area.x = mAnimationRowSettings[ mCurrentAnimationRow ].ClipSize.Width * mAnimationRowStatus[ mCurrentAnimationRow ].CurrentAnimationFrame;
   clip_area.w = mAnimationRowSettings[ mCurrentAnimationRow ].ClipSize.Width;
   clip_area.h = mAnimationRowSettings[ mCurrentAnimationRow ].ClipSize.Height;
   SDL_RenderCopy ( mRenderer , mTexture , &clip_area , &destination_area );
   return;
}

void AnimatedSprite::resetAnimation ( void )
{
   std::size_t size;
   size = mAnimationRowStatus.size ();

   for ( std::size_t i = 0; i < size; i++ )
      mAnimationRowStatus[ i ].reset ();

   return;
}

void AnimatedSprite::setAnimationSettings ( const unsigned int& pRowToConfigure ,
                                            const AnimationRowSettings& pAnimationSettings )
{
   if ( mAnimationRowSettings.size () <= pRowToConfigure )
   {
      // Generate a default status structure to manage the status vector
      AnimationStatus status;

      // Fill the settings configuration vector with copies of the data passed until I reach the index required.
      while ( mAnimationRowSettings.size () <= pRowToConfigure )
      {
         mAnimationRowSettings.push_back ( pAnimationSettings );
         mAnimationRowStatus.push_back ( status );
      }
   }
   else
      mAnimationRowSettings[ pRowToConfigure ] = pAnimationSettings;

   return;
}

void AnimatedSprite::setCurrentAnimationFrame ( const unsigned int& pNewAnimationFrame )
{
   mAnimationRowStatus[ mCurrentAnimationFrame ].CurrentAnimationFrame = pNewAnimationFrame;
   return;
}

void AnimatedSprite::setCurrentAnimationRow ( const unsigned int& pNewAnimationRow )
{
   if ( pNewAnimationRow >= mAnimationRowSettings.size () )
      mCurrentAnimationRow = 0;
   else
      mCurrentAnimationRow = pNewAnimationRow;

   return;
}

void AnimatedSprite::updateTime ( const double& pTimeDelta )
{
   // NOTE: The "LoopAnimation" flag only is validated when there is no loop delay. If there is loop delay time, then we assume that the animation should loop.

   // Update the current animation row status
   mAnimationRowStatus[ mCurrentAnimationRow ].CurrentFrameTime += static_cast< unsigned int > ( pTimeDelta );

   // Are we in time loop delay?
   if ( mAnimationRowStatus[ mCurrentAnimationRow ].IsInLoopDelay )
   {
      // We are in a loop delay. Have we reached such delay?
      if ( mAnimationRowStatus[ mCurrentAnimationRow ].CurrentFrameTime >= mAnimationRowSettings[ mCurrentAnimationRow ].LoopDelay )
      {
         // We just finished the delay time, so, reset the frame, deactivate the loop delay flag and append remaining time to the next frame.
         mAnimationRowStatus[ mCurrentAnimationRow ].CurrentAnimationFrame = 0;
         mAnimationRowStatus[ mCurrentAnimationRow ].CurrentFrameTime -= mAnimationRowSettings[ mCurrentAnimationRow ].LoopDelay;
         mAnimationRowStatus[ mCurrentAnimationRow ].IsInLoopDelay = false;
      }
   }
   // We are not currently in a loop delay. Check if we just reached the current frame time.
   else if ( mAnimationRowStatus[ mCurrentAnimationRow ].CurrentFrameTime >= mAnimationRowSettings[ mCurrentAnimationRow ].FrameTime )
   {
      // We just finished the current frame time. Progress one frame and reduce the accumulated frame time.
      mAnimationRowStatus[ mCurrentAnimationRow ].CurrentAnimationFrame++;
      mAnimationRowStatus[ mCurrentAnimationRow ].CurrentFrameTime -= mAnimationRowSettings[ mCurrentAnimationRow ].FrameTime;

      // Did we just finished the available frames?
      if ( mAnimationRowStatus[ mCurrentAnimationRow ].CurrentAnimationFrame >= mAnimationRowSettings[ mCurrentAnimationRow ].FramesInRow )
      {
         // We just reached the last frame and finished displaying it. Should we wait with a delay?
         if ( mAnimationRowSettings[ mCurrentAnimationRow ].LoopDelay == 0 )
         {
            // There is no loop delay time. Shall we loop the animation?
            if ( mAnimationRowSettings[ mCurrentAnimationRow ].LoopAnimation )
               mAnimationRowStatus[ mCurrentAnimationRow ].CurrentAnimationFrame = 0;
            else
            {
               // We don't need to loop, so, we just finished working here. Mark the animation as finished, but don't
               // forget to reset the counter of the frame index so we don't have an out-of-bounds exception and we
               // are still able to draw the last frame.
               mAnimationRowStatus[ mCurrentAnimationRow ].IsAnimationFinished = true;
               mAnimationRowStatus[ mCurrentAnimationRow ].CurrentAnimationFrame--;
            }
         }
         else
         {
            // There is loop delay time. So, append the current delay time to such counter of time and move the frame index to the previous one.
            // Also, don't forget to enable the flag to remember that we are right now in a loop delay.
            mAnimationRowStatus[ mCurrentAnimationRow ].IsInLoopDelay = true;
            mAnimationRowStatus[ mCurrentAnimationRow ].CurrentAnimationFrame--;
         }
      }
      // No, we haven't finished displaying frames, continue as normal.
   }
   // No, we haven't reached the current frame time.

   return;
}