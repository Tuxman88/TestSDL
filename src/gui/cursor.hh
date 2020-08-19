# ifndef CURSOR_HH_
# define CURSOR_HH_

# include "animatedelement.hh"

class Cursor : public AnimatedElement
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

      /**
       * Virtual member function used to update the element accordingly to the passage of time.
       * 
       * @param[in] pTimeDelta Update the visual component according to the time passage.
       */
      virtual void updateTime ( const double& pTimeDelta );
};

# endif