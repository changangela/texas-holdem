#include "Hand.h"
#include <algorithm>
#include <sstream>

Hand::Hand() {
	// constructor method initializes class variables.
	m_rank = TWO;
	m_status = ONLY_SINGLES;
}
Hand::~Hand() {
	// when the instance is destructed, all cards from vector are removed.
	m_hand.erase(m_hand.begin(), m_hand.begin() + SIZE_POKER_HAND);
}
void Hand::dealHand(Dealer &dealer) {
	// 5 cards are dealt to this hand from the dealer's deck.
	for (int i = 0; i < SIZE_POKER_HAND; i++) {
		m_hand.push_back(dealer.dealNextCard());
	}
}
void Hand::dealCard(Dealer &dealer, int num) {
	// 'num' cards are dealt to this hand from the dealer's deck.
	for (int i = 0; i < num; i++) {
		m_hand.push_back(dealer.dealNextCard());
	}
}
void Hand::printHand() {
	// prints the names of all the current cards in the hand.
	cout << endl << "| ";
	for (int i = 0; i < static_cast<signed int>(m_hand.size()); i++) {
		cout << m_hand[i].toString() << " | ";
	}
	cout << endl;
}
void Hand::newHand() {
	// removes all the cards from the hand.
	m_hand.erase(m_hand.begin(),
			m_hand.begin() + static_cast<signed int>(m_hand.size()));
}
void Hand::updateStatus() {
	// this function is used to determine the 'status' of the hand.

	// the frequency counter is updated and the hand is sorted by card strength.
	updateFrequencies();
	sortHand();

	// the number of doubles, triples, and quadruples are counted.
	int numSingles = OneOfAKind();
	int numPairs = TwoOfAKind();
	int numTriples = ThreeOfAKind();
	int numQuadruples = FourOfAKind();

	// the flush or straight properties of hand is determined.
	bool flush = isFlush();
	bool straight = isStraight();

	if (numSingles == 5) {
		// if all 5 cards are singles.
		m_status = ONLY_SINGLES;
		if (flush)
			// check for flush.
			m_status = (straight) ? STRAIGHT_FLUSH : ONLY_FLUSH;
		else if (straight)
			// check for straight.
			m_status = ONLY_STRAIGHT;
	} else {
		if (numPairs == 1)
			// if there is 1 pair, check for a triple; if not found it is not full house.
			m_status = (numTriples == 1) ? FULL_HOUSE : ONE_PAIR;
		else if (numPairs == 2)
			// check for 2 pairs.
			m_status = TWO_PAIRS;
		else {
			if (numTriples == 1)
				// check for three of a kind.
				m_status = THREE_OF_A_KIND;
			else if (numQuadruples == 1)
				// check for quadruples.
				m_status = FOUR_OF_A_KIND;
		}
	}

	updateRank();
}
void Hand::updateRank() {
	// this function updates the rank of the hand given its status. This is for making comparisons should the other player have same statused cards.
	if (m_status == STRAIGHT_FLUSH || m_status == ONLY_FLUSH
			|| m_status == ONLY_STRAIGHT || m_status == ONLY_SINGLES) {
		// if only singles, straight, or flush, the value of importance is its highest card.
		m_rank = static_cast<Rank>(m_hand[4].getRank());
	}
	if (m_status == FOUR_OF_A_KIND) {
		// if four of a kind, the value of importance is the rank of the 4 of a kind cards.
		for (int i = 0; i < 13; i++) {
			if (frequencies[i] == 4)
				m_rank = static_cast<Rank>(i);
		}
	}
	if (m_status == FULL_HOUSE || m_status == THREE_OF_A_KIND) {
		// if three of a kind or full house, the value of importance is the rank of the 3 of a kind cards.
		for (int i = 0; i < 13; i++) {
			if (frequencies[i] == 3)
				m_rank = static_cast<Rank>(i);
		}
	}
	if (m_status == TWO_PAIRS || m_status == ONE_PAIR) {
		// if one pair or more, the value of importance is the rank of the highest paired cards.
		for (int i = 0; i < 13; i++) {
			if (frequencies[i] == 2)
				m_rank = static_cast<Rank>(i);
		}
	}

}
void Hand::sortHand() {
	// this function sorts the cards from least value to highest value using a selection sort.
	// this is useful in order to find high card more efficiently, and also determine straight properties.

	int minIndex;
	Cards temp;

	for (int i = 0; i < static_cast<signed int>(m_hand.size()); i++) {
		minIndex = i;

		for (int j = i; j < static_cast<signed int>(m_hand.size()); j++) {
			if (m_hand[j].getRank() < m_hand[minIndex].getRank())
				minIndex = j;
		}

		swap(m_hand[minIndex], m_hand[i]);
	}
}
void Hand::updateFrequencies() {
	// this function loops through cards in the players hand, and adds 1 to the appropriate frequency counter for the card faces from 2-A.
	for (int i = 0; i < 13; i++) {
		frequencies[i] = 0;
	}
	for (int i = 0; i < static_cast<signed int>(m_hand.size()); i++) {
		frequencies[m_hand[i].getFace()]++;
	}
}
int Hand::FourOfAKind() {
	// counts the number of faces with the frequency of 4 cards in hand.
	int counter = 0;
	for (int i = 0; i < 13; i++) {
		if (frequencies[i] == 4) {
			counter++;
		}
	}
	return counter;
}
int Hand::ThreeOfAKind() {
	// counts the number of faces with the frequency of 3 cards in hand.
	int counter = 0;
	for (int i = 0; i < 13; i++) {
		if (frequencies[i] == 3) {
			counter++;
		}
	}
	return counter;
}
int Hand::TwoOfAKind() {
	// counts the number of faces with the frequency of 2 cards in hand.
	int counter = 0;
	for (int i = 0; i < 13; i++) {
		if (frequencies[i] == 2) {
			counter++;
		}
	}
	return counter;
}
int Hand::OneOfAKind() {
	// counts the number of faces with the frequency of 1 card in hand.
	int counter = 0;
	for (int i = 0; i < 13; i++) {
		if (frequencies[i] == 1) {
			counter++;
		}
	}
	return counter;
}
bool Hand::isFlush() {
	// this function checks for a flush.
	// using the first card's suit as comparision, if any card doesn't have the same suit, it is not a flush.
	if (m_hand.size() == 5) {
		int commonSuit = m_hand[0].getSuit();
		for (int i = 0; i < static_cast<signed int>(m_hand.size()); i++) {
			if (m_hand[i].getSuit() != commonSuit)
				return false;
		}
		return true;
	}

	return false;
}
bool Hand::isStraight() {
	// function checks if hand is a straight.
	// using a sorted deck, if hand is a straight, each card should be one face higher accumulatively.
	if (m_hand.size() == 5) {
		int lowestNumber = m_hand[0].getFace();
		for (int i = 0; i < static_cast<signed int>(m_hand.size()); i++) {
			if (m_hand[i].getFace() != lowestNumber + i) {
				if (lowestNumber == 0 && i == 4) {
					if (m_hand[i].getFace() != 12)
						return false;
				} else {
					return false;
				}

			}
		}

		return true;
	}
	return false;
}
int Hand::getSizeOfHand() {
	// returns the number of cards currently in hand.
	return static_cast<signed int>(m_hand.size());
}
string Hand::getStatus() {
	// this function returns the status of the hand in string output.

	updateStatus();

	switch (m_status) {
	case STRAIGHT_FLUSH:
		return "Straight-Flush";
	case FOUR_OF_A_KIND:
		return "Four of a Kind";
	case FULL_HOUSE:
		return ("Full House");
	case ONLY_FLUSH:
		return ("Flush");
	case ONLY_STRAIGHT:
		return ("Straight");
	case THREE_OF_A_KIND:
		return "Three of a Kind";
	case TWO_PAIRS:
		return "Two Pairs";
	case ONE_PAIR:
		return "One Pair";
	default:
		string temp = "Only Singles: " + m_hand[4].getFaceWord() + " High";
		return temp;
	}
}
char Hand::getFaceChar(int index) {
	// returns the face in character form of the 'index' card.
	return m_hand[index].getFaceChar();
}
char Hand::getSuitChar(int index) {
	// returns the suit in character form of the 'index' card.
	return m_hand[index].getSuitChar();
}
int Hand::getStatusID() {
	// the status ID is a way of comparing the winner when both players have the same statused hand.
	// the winner would be the one with the highest rank.
	updateStatus();
	return m_status * 100 + m_rank;
}

