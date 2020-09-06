# ifndef ANIMATEDSPRITE_HH_
# define ANIMATEDSPRITE_HH_

# include <vector>

# include "visualelement.hh"

class AnimatedSprite : public VisualElement
{
   public:
      struct AnimationRowSettings
      {
         AnimationRowSettings ( void )
            : FramesInRow ( 1 ) ,
              LoopAnimation ( true ) ,
              FrameTime ( 1000000 / 10 ) , // Time in microseconds for 10 FPS
              LoopDelay ( 1000000 / 10 ) // Time in microseconds before starting the animation again.
         {
         }

         VisualElement::Size ClipSize;
         unsigned int FramesInRow;
         bool LoopAnimation;
         unsigned int FrameTime;
         unsigned int LoopDelay;
      };

      struct AnimationStatus
      {
         AnimationStatus ( void )
            : CurrentAnimationFrame ( 0 ) ,
              CurrentFrameTime ( 0 ) ,
              IsInLoopDelay ( false ) ,
              IsAnimationFinished ( false )
         {
         }

         void reset ( void )
         {
            CurrentAnimationFrame = 0;
            CurrentFrameTime = 0;
            IsInLoopDelay = false;
            IsAnimationFinished = false;

            return;
         }

         unsigned int CurrentAnimationFrame;
         unsigned int CurrentFrameTime;
         bool IsInLoopDelay;
         bool IsAnimationFinished;
      };

      /**
       * Explicit default constructor.
       */
      explicit AnimatedSprite ( void );

      /**
       * Virtual destructor.
       */
      virtual ~AnimatedSprite ( void );

      /**
       * Member function used to retrieve the current animation status of the current row.
       * 
       * @returns Current animation status.
       */
      AnimationStatus currentAnimationStatus ( void ) const;

      /**
       * Member function used to retrieve the current animation row of the current image.
       * 
       * @returns Current animation row index.
       */
      virtual unsigned int currentAnimationRow ( void ) const;

      /**
       * Virtual member function used to draw the current figure, if needed.
       */
      virtual void draw ( void ) override;

      /**
       * Member function used to reset the current animation status.
       */
      virtual void resetAnimation ( void );

      /**
       * Member function used to set the settings required for the specified animation row.
       * 
       * @param[in] pRowToConfigure Row index to configure. If the row specified is new, a new number of settings will be created as copies of this one.
       * @param[in] pAnimationSettings Configuration to set in the animation.
       */
      virtual void setAnimationSettings ( const unsigned int& pRowToConfigure ,
                                          const AnimationRowSettings& pAnimationSettings );

      /**
       * Member function used to set the current animation frame to display.
       * 
       * @param[in] pNewAnimationFrame New animation frame index to set.
       */
      virtual void setCurrentAnimationFrame ( const unsigned int& pNewAnimationFrame );

      /**
       * Member function used to set the current animation row to configure.
       * 
       * @param[in] pNewAnimationRow New animation row to use from those configured.
       */
      virtual void setCurrentAnimationRow ( const unsigned int& pNewAnimationRow );

      /**
       * Virtual member function used to update the element accordingly to the passage of time.
       * 
       * @param[in] pTimeDelta Update the visual component according to the time passage.
       */
      virtual void updateTime ( const double& pTimeDelta ) override;

   protected:
      unsigned int mCurrentAnimationFrame; /**< Current frame to display of the current animation row. */
      unsigned int mCurrentAnimationRow;   /**< Current animation row of the current image. */

      std::vector< AnimationRowSettings > mAnimationRowSettings; /**< Vector containing the settings for all the rows of animation. */

      std::vector< AnimatedSprite::AnimationStatus > mAnimationRowStatus; /**< Vector containing the current status of the animations. */
};

# endif