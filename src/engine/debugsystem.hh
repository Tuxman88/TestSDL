# ifndef DEBUGSYSTEM_HH_
# define DEBUGSYSTEM_HH_

# include <fstream>
# include <string>
# include <sstream>

# include "systemcomponent.hh"

template< class T >
std::string ToString ( const T& pValue )
{
   std::stringstream processor;
   std::string result;

   processor << pValue;
   processor >> result;

   return ( result );
}

int FromString ( const std::string& pValue );
bool IsInteger ( const std::string& pValue );

class DebugSystem : public SystemComponent
{
   public:
      /**
       * Explicit default constructor.
       */
      explicit DebugSystem ( void );

      /**
       * Virtual destructor.
       */
      virtual ~DebugSystem ( void );

      /**
       * Virtual member function used to initialize the debug system.
       */
      virtual bool init ( void ) override;

      /**
       * Member function used to log a message to a file.
       * 
       * @param[in] pMessage String message to add to the log file.
       */
      void logToFile ( const std::string& pMessage );

      /**
       * Virtual member function used to terminate the functionality of the debug system.
       */
      virtual void terminate ( void ) override;

   private:
      std::ofstream mLogFile; /**< Output file for the regular log lines. */
};

# endif