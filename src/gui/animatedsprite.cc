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

unsigned int AnimatedSprite::currentAnimationFrame ( void ) const
{
   return ( mCurrentAnimationFrame );
}

unsigned int AnimatedSprite::currentAnimationRow ( void ) const
{
   return ( mCurrentAnimationRow );
}