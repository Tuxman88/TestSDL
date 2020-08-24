# ifndef SEA_HH_
# define SEA_HH_

# include "terrain.hh"

class Sea : public Terrain
{
   public:
      /**
       * Explicit default constructor.
       */
      explicit Sea ( void );

      /**
       * Virtual destructor.
       */
      virtual ~Sea ( void );
};

# endif