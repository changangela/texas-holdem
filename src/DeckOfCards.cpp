#include "DeckOfCards.h"
#include <cstdlib>

using namespace std;

DeckOfCards::DeckOfCards() {
	// constructor method initializes the deck of cards by adding 52 unshuffled cards into deck.
	m_deck = new Cards[SIZE_OF_DECK];
	m_currentCard = 0;
	for (int i = 0; i < SIZE_OF_DECK; i++) {
		m_deck[i].setFace(i % 13); // assigns face in systematic order.
		m_deck[i].setSuit(i / 13); // assigns suit in systematic order.
	}
}
DeckOfCards::~DeckOfCards() {
	// since deck of cards was stored on the heap, it requires manual deconstructing.
	delete[] m_deck;
}
void DeckOfCards::shuffle() {
	// function shuffles the cards by iterating through each card of the deck and swapping it with a randomly selected card.

	Cards tempCard;
	int randomNumber;

	for (int i = 0; i < SIZE_OF_DECK; i++) {
		randomNumber = rand() % SIZE_OF_DECK;
		tempCard = m_deck[randomNumber];
		m_deck[randomNumber] = m_deck[i];
		m_deck[i] = tempCard;
	}
}
Cards DeckOfCards::dealCard() {
	// functions returns a card to the caller.
	// the top card in the deck is dealt.
	m_currentCard++;
	return m_deck[m_currentCard - 1];
}
bool DeckOfCards::moreCards() {
	// if the currentCard value is greater than the size of the deck, there are no more cards that can be dealt.
	return (m_currentCard >= SIZE_OF_DECK) ? false : true;
}
int DeckOfCards::getSizeOfDeck() {
	// returns the deck size.
	return SIZE_OF_DECK;
}

