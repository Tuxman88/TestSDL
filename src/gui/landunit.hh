# ifndef LANDUNIT_HH_
# define LANDUNIT_HH_

# include "animatedsprite.hh"
# include "visualelement.hh"

class LandUnit : public VisualElement
{
   public:
      enum class LandUnitType
      {
         None ,
         ForestTree ,
         SnowTree ,
         Mech ,
         Structure
      };

      /**
       * Explicit constructor.
       */
      explicit LandUnit ( void );

      /**
       * Virtual destructor.
       */
      virtual ~LandUnit ( void );

      /**
       * Member function used to move the current coordinates according to the deltas provided.
       * 
       * @param[in] pXDelta X movement.
       * @param[in] pYDelta Y movement.
       */
      virtual void move ( const int& pXDelta , 
                          const int& pYDelta ) override;

      /**
       * Member function used to set the current land unit type.
       * 
       * @param[in] pNewType New type to set.
       */
      virtual void setType ( const LandUnitType& pNewType );

      /**
       * Member function used to return the current land unit type.
       * 
       * @returns Current terrain type.
       */
      virtual LandUnitType type ( void ) const;

   protected:
      LandUnitType   mLandUnitType; /**< Type of unit.*/
      AnimatedSprite mUnitSprite;   /**< Sprite to draw unit. */
      Position       mMoveOffset;   /**< Offset stored to apply in the unit. */
};

# endif
