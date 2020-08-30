# include "debugsystem.hh"

int FromString ( const std::string& pValue )
{
   std::stringstream processor;
   int result = 0;

   processor << pValue;
   processor >> result;
   return ( result );
}

bool IsInteger ( const std::string& pValue )
{
   for ( std::size_t i = 0; i < pValue.size (); i++ )
      if ( pValue.at ( i ) < '0'
           || pValue.at ( i ) > '9' )
         return ( false );

   return ( true );
}

DebugSystem::DebugSystem ( void )
   : SystemComponent ()
{
}

DebugSystem::~DebugSystem ( void )
{
   terminate ();
}

bool DebugSystem::init ( void )
{
   mLogFile.open ( "output.txt" );
   return ( true );
}

void DebugSystem::logToFile ( const std::string& pMessage )
{
   if ( mLogFile.is_open () )
   {
      mLogFile << pMessage << "\n";
      mLogFile.flush ();
   }

   return;
}

void DebugSystem::terminate ( void )
{
   if ( mLogFile.is_open () )
      mLogFile.close ();

   return;
}