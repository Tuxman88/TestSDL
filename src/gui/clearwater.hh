# ifndef CLEARWATER_HH_
# define CLEARWATER_HH_

# include "sea.hh"

class ClearWater : public Sea
{
   public:
      /**
       * Explicit default constructor.
       */
      explicit ClearWater ( void );

      /**
       * Virtual destructor.
       */
      virtual ~ClearWater ( void );

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