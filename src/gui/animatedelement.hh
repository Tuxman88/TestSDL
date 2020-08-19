# ifndef ANIMATEDELEMENT_HH_
# define ANIMATEDELEMENT_HH_

# include "graphicelement.hh"

class AnimatedElement : public GraphicElement
{
   public:
      explicit AnimatedElement ( void );
      virtual ~AnimatedElement ( void );

   protected:
      int mCurrentFrame;
};

# endif