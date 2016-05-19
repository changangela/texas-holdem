#include <iostream>
#include <string>
#include "Cards.h"

using namespace std;

#ifndef DECKOFCARDS_H_
#define DECKOFCARDS_H_

class DeckOfCards {
private:
	static const int SIZE_OF_DECK = 52; // deck has a constant value of 52 cards (no jokers).
	int m_currentCard; // the next available card; every previous card has already been dealt.
	Cards *m_deck; // pointer of cards to store the deck.
public:
	DeckOfCards();
	~DeckOfCards();
	void shuffle();

	Cards dealCard();
	bool moreCards();
	int getSizeOfDeck();

};

#endif /* DECKOFCARDS_H_ */
