# ifndef SYSTEMCOMPONENT_HH_
# define SYSTEMCOMPONENT_HH_

class SystemComponent
{
   public:
      /**
       * Explicit default constructor.
       */
      explicit SystemComponent ( void );

      /**
       * Virtual destructor.
       */
      virtual ~SystemComponent ( void );

      /**
       * Pure virtual member function used to initialize the system component.
       * 
       * @returns "true" if the initialization succeeds, "false" if not.
       */
      virtual bool init ( void ) = 0;

      /**
       * Pure virtual member function used to terminate the current system component.
       */
      virtual void terminate ( void ) = 0;
};

# endif