#include "Dealer.h"

#include <vector>

#ifndef HAND_H_
#define HAND_H_

class Hand {
	// this class defines the up to 5 cards each player holds.
	enum Rank{
		// the Rank is the value of importance. ie. Full House with three 8's and two 4's has a Rank = 8.
		TWO,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		EIGHT,
		NINE,
		TEN,
		JACK,
		QUEEN,
		KING,
		ACE
	};
	enum Status{
		// the status is the pokerhand definition for the 5 card hand.
		ONLY_SINGLES,
		ONE_PAIR,
		TWO_PAIRS,
		THREE_OF_A_KIND,
		ONLY_STRAIGHT,
		ONLY_FLUSH,
		FULL_HOUSE,
		FOUR_OF_A_KIND,
		STRAIGHT_FLUSH

	};

private:
	static const int SIZE_POKER_HAND = 5;
	vector<Cards> m_hand; // a vector of cards is created to store the 0-5 cards.

	int frequencies[13]; // the number of each face, used to determine pairs, triples, etc.
	Status m_status; // the status is the pokerhand definition for the 5 card hand. ie. Full House
	Rank m_rank; // the Rank is the value of importance. ie. Full House with three 8's and two 4's has a Rank = EIGHT.

	void updateFrequencies();
	void updateStatus();
	void updateRank();
	void sortHand();

	int FourOfAKind();
	int ThreeOfAKind();
	int TwoOfAKind();
	int OneOfAKind();

	bool isFlush();
	bool isStraight();

public:
	Hand();
	~Hand();
	void dealHand(Dealer &dealer);
	void dealCard(Dealer &dealer,int num);
	void printHand();
	void newHand();

	int getSizeOfHand();
	char getFaceChar(int index);
	char getSuitChar(int index);
	string getStatus();
	int getStatusID();

};

#endif /* HAND_H_ */
