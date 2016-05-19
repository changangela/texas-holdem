/*
 * NOTE: instead of modifying this class for the bonus portion of the assignment, I decided to create a new class
 * called 'Hand' in order to store the players hand, determine pokerhand status, along with a variety
 * of other actions.
 */

#include "Dealer.h"

Dealer::Dealer() {
	// the constructor method where the dealer is given a fresh deck, and immediately shuffles the deck.
	m_dealerDeck.shuffle();
}
void Dealer::dealDeck() {
	// the dealer deals out the entire rest of deck.
	while (m_dealerDeck.moreCards()) {
		// if there are more cards, keep dealing.
		Cards newCard = m_dealerDeck.dealCard();
		cout << newCard.toString() << endl;
	}
}
void Dealer::newDeck() {
	// the deck is manually destructed and reconstructed.
	// this is for when the deck runs out of cards and the dealer requires a new deck to play with.
	(&m_dealerDeck)->~DeckOfCards();
	new (&m_dealerDeck) DeckOfCards();

	// the deck is shuffled.
	m_dealerDeck.shuffle();
}
int Dealer::getDeckSize() {
	// returns the amount of cards in current deck.
	return m_dealerDeck.getSizeOfDeck();
}
Cards Dealer::dealNextCard() {
	// function returns the top card of the deck.
	if (!m_dealerDeck.moreCards()) {
		// if there are no more cards, a new deck is required (deck deconstructed and reconstructed).
		(&m_dealerDeck)->~DeckOfCards();
		new (&m_dealerDeck) DeckOfCards();
		m_dealerDeck.shuffle();
	}

	return m_dealerDeck.dealCard();
}

