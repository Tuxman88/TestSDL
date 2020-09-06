# include <ctime>
# include <cstdlib>
# include <iostream>
# include "src/game.hh"

int main ( int argc , char* argv[] )
{
	// Initialize random number generation seed
	srand ( static_cast< unsigned int > ( time ( nullptr ) ) );

	Game game;
	
	if ( !game.init () )
		return ( 1 );

	game.start ();

	return ( 0 );
}