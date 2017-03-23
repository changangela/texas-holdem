/*
 * NOTE: instead of modifying this class for the bonus portion of the assignment, I decided to create a new class
 * called 'Hand' in order to store the players hand, determine pokerhand status, along with a variety
 * of other actions.
 */

#include "DeckOfCards.h"

#ifndef DEALER_H_
#define DEALER_H_

class Dealer {
private:
	DeckOfCards m_dealerDeck; // the dealer is equipped with a deck of cards.
public:
	Dealer();
	void dealDeck();
	void newDeck();

	Cards dealNextCard();
	int getDeckSize();

};

#endif /* DEALER_H_ */
