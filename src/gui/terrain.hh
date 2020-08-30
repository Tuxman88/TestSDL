# ifndef TERRAIN_HH_
# define TERRAIN_HH_

# include "visualelement.hh"

class Terrain : public VisualElement
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