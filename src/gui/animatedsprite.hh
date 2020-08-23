# ifndef ANIMATEDSPRITE_HH_
# define ANIMATEDSPRITE_HH_

# include "visualelement.hh"

class AnimatedSprite : public VisualElement
{
   public:
      /**
       * Explicit default constructor.
       */
      explicit AnimatedSprite ( void );

      /**
       * Virtual destructor.
       */
      virtual ~AnimatedSprite ( void );

      /**
       * Member function used to retrieve the current animation frame of the current row.
       * 
       * @returns Current animation frame.
       */
      unsigned int currentAnimationFrame ( void ) const;

      /**
       * Member function used to retrieve the current animation row of the current image.
       * 
       * @returns Current animation row index.
       */
      unsigned int currentAnimationRow ( void ) const;

   protected:
      unsigned int mCurrentAnimationFrame; /**< Current frame to display of the current animation row. */
      unsigned int mCurrentAnimationRow;   /**< Current animation row of the current image. */
};

# endif