#include "Hand.h"

#ifndef PLAYER_H_
#define PLAYER_H_

class Player {
private:
	Hand m_playerHand; // each player has his own hand containing up to 5 cards.
	int m_money; // each player has a wallet.
	string m_name;// each player has a name.
public:
	Player();
	virtual ~Player();
	void dealHand(Dealer &dealer);
	void dealCard(Dealer &dealer, int num);

	void newHand();
	void printHand();
	void printHandCaption();

	void winAmount(int money);
	void loseAmount(int money);
	void setAmount(int money);
	void setName(string name);

	int getAmount();
	string getName();
	string getStatus();
	int getStatusID();

};

#endif /* PLAYER_H_ */
