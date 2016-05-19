#include "player.h"

#ifndef POKERGAME_H_
#define POKERGAME_H_

class PokerGame {
private:
	// A dealer was created, a computerAI, and a player was created.
	Dealer m_dealer; // this object possesses the deck of cards and deals the cards to the m_players.
	Player m_player, m_cpuAI; // these objects store the money, pokerHand, and actions.
	int m_currentBet, m_currentAmount, m_currentPot; // bet is the amount including raises, amount is the raised amount, pot is the entire pot accumulation.
	bool m_gameOver; // determines whether the round has concluded.
	static const int COST = 10; // the cost of game is 10$.

	void pauseScreen();
	void printInfo();
	void Round1();
	void RoundN();
	void restart();
	void compare();
	void flop(Player &p_player, Player &p_other);
	void call(Player &p_player);
	void raisePlayer();
	void raiseComputer();
	void playerAction();
	void computerAction();

public:
	void initialize();
	PokerGame();
};

#endif /* POKERGAME_H_ */
