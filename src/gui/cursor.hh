# ifndef CURSOR_HH_
# define CURSOR_HH_

# include "animatedsprite.hh"

class Cursor : public AnimatedSprite
{
   public:
      enum class CursorState
      {
         Normal = 0 ,
         Hover = 1 ,
         Click = 2
      };

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
       * Member function used to set the current cursor state.
       * 
       * @param[in] pNewCursorState New cursor state to set.
       */
      void setState ( const CursorState& pNewCursorState );

      /**
       * Virtual member function used to update the element accordingly to the passage of time.
       * 
       * @param[in] pTimeDelta Update the visual component according to the time passage.
       */
      virtual void updateTime ( const double& pTimeDelta );

   private:
      CursorState mCursorState; /**< Current cursor state, which also affects the current animation. */
};

# endif