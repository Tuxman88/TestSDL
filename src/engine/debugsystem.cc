# include "debugsystem.hh"

int FromString ( const std::string& pValue )
{
   std::stringstream processor;
   int result = 0;

   processor << pValue;
   processor >> result;

   return ( result );
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
   {
      mLogFile.close ();
   }

   return;
}