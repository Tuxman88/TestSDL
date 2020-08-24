# ifndef TERRAIN_HH_
# define TERRAIN_HH_

# include "animatedsprite.hh"

class Terrain : public AnimatedSprite
{
   public:
      /**
       * Explicit default constructor.
       */
      explicit Terrain ( void );

      /**
       * Virtual destructor.
       */
      virtual ~Terrain ( void );
};

# endif