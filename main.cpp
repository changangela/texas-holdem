
#include <iostream>
#include <ctime>
#include <cstdlib>

#include "PokerGame.h"

using namespace std;

int main() {
	srand(static_cast<unsigned int>(time(0)));

	// instance of a game is created and initialized.
	PokerGame game;
	game.initialize();

}
