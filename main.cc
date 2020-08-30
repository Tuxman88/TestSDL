# include <iostream>
# include "src/game.hh"

int main ( int argc , char* argv[] )
{
	Game game;
	
	if ( !game.init () )
		return ( 1 );

	game.start ();

	return ( 0 );
}