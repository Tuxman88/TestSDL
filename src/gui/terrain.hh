# ifndef TERRAIN_HH_
# define TERRAIN_HH_

# include "visualelement.hh"

class Terrain : public VisualElement
{
   public:
      enum class TerrainType
      {
         Sea = 0
      };

      /**
       * Explicit default constructor.
       */
      explicit Terrain ( void );

      /**
       * Virtual destructor.
       */
      virtual ~Terrain ( void );

      /**
       * Member function used to set the current terrain type.
       * 
       * @param[in] pNewType New type to set.
       */
      void setType ( const TerrainType& pNewType );

      /**
       * Member function used to return the current terrain type.
       * 
       * @returns Current terrain type.
       */
      virtual TerrainType type ( void ) const;

   protected:
      TerrainType mTerrainType;
};

# endif