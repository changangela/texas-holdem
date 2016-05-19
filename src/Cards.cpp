#include "Cards.h"

using namespace std;

Cards::Cards() {
	// default constructor initializes the card to the 2 of diamonds (weakest card in poker).
	m_face = 0;
	m_suit = 0;
}
Cards::Cards(int face, int suit) {
	// constructor sets the face and suit when being constructed.
	setFace(face);
	setSuit(suit);
}
int Cards::getFace() {
	// returns the face of the card.
	return m_face;
}
int Cards::getSuit() {
	// returns the suit of the card.
	return m_suit;
}
int Cards::getRank() {
	// each card in the deck has a rank between 1 and 52 (from weakest to strongest).
	// the ranking is based on face (major) and suit (minor).
	return m_face * 4 + m_suit;
}
char Cards::getFaceChar() {
	// returns the corresponding character symbols for the face of the card.
	switch (m_face) {
	case 0:
		return '2';
	case 1:
		return '3';
	case 2:
		return '4';
	case 3:
		return '5';
	case 4:
		return '6';
	case 5:
		return '7';
	case 6:
		return '8';
	case 7:
		return '9';
	case 8:
		return 'T';
	case 9:
		return 'J';
	case 10:
		return 'Q';
	case 11:
		return 'K';
	default:
		return 'A';
	}

}
string Cards::getFaceWord() {
	// returns the corresponding word for the face of card.
	string m_faces[13] = { "Two", "Three", "Four", "Five", "Six", "Seven",
			"Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace" };
	return m_faces[m_face];
}
char Cards::getSuitChar() {
	// returns the corresponding suit character for the card.
	switch (m_suit) {
	case 0:
		return 'D';
	case 1:
		return 'C';
	case 2:
		return 'H';
	default:
		return 'S';
	}
}
void Cards::setFace(int face) {
	// sets the face of the card to the parameter.
	if (face >= 0 && face < 13)
		// if the input was not an appropriate number, the face member was not changed.
		m_face = face;
	else
		m_face = 0;
}
void Cards::setSuit(int suit) {
	// sets the suit member of card to parameter.
	if (suit >= 0 && suit < 4)
		// if the input was not an appropriate number, it was not changed.
		m_suit = suit;
	else
		m_suit = 0;
}
string Cards::toString() {
	// returns the name of card. ie. Two of Diamonds.
	string m_faces[13] = { "Two", "Three", "Four", "Five", "Six", "Seven",
			"Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace" };
	string m_suits[4] = { "Diamonds", "Clubs", "Hearts", "Spades" };
	return m_faces[m_face] + " of " + m_suits[m_suit];
}
