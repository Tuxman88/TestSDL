# ifndef CURSOR_HH_
# define CURSOR_HH_

# include "graphicelement.hh"

class Cursor : public GraphicElement
{
   public:
      /**
       * Explicit default constructor.
       */
      explicit Cursor ( void );

      /**
       * Virtual destructor.
       */
      virtual ~Cursor ( void );

      /**
       * Virtual member function used to draw the current figure, if needed.
       */
      virtual void draw ( void );
};

# endif