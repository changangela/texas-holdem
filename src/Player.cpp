#include "Player.h"

Player::Player() {
	// constructor method initializes wallet and name.
	m_money = 1000; // each player starts with $1000.
	m_name = "Computer";
}
Player::~Player() {
	// no need to destroy class instances stored on stack.
}

void Player::dealHand(Dealer &dealer) {
	// the dealer removes 5 cards from his deck and deals them to the player.
	m_playerHand.dealHand(dealer);
}
void Player::dealCard(Dealer &dealer, int num) {
	// the dealer removes 'num' cards from the deck and deals them to player.
	m_playerHand.dealCard(dealer, num);
}
void Player::printHand() {
	// the cards are printed using console graphics side by side.

	m_playerHand.printHand(); // the name of cards are printed out.

	int numCards = m_playerHand.getSizeOfHand();

	// draw _____ for each card.
	for (int i = 0; i < numCards; i++) {
		cout << "\t _____";
	}
	cout << endl;

	//draw |     | for each card.
	for (int i = 0; i < numCards; i++) {
		cout << "\t|     |";
	}
	cout << endl;

	//draw |  F  | for each card.
	for (int i = 0; i < numCards; i++) {
		cout << "\t|  " << m_playerHand.getFaceChar(i) << "  |";
	}
	cout << endl;

	//draw |  S  | for each card.
	for (int i = 0; i < numCards; i++) {
		cout << "\t|  " << m_playerHand.getSuitChar(i) << "  |";
	}
	cout << endl;

	//draw |     | for each card.
	for (int i = 0; i < numCards; i++) {
		cout << "\t|     |";
	}
	cout << endl;

	//draw ¯¯¯¯¯ for each card.
	for (int i = 0; i < numCards; i++) {
		cout << "\t ¯¯¯¯¯";
	}
	cout << endl;
}
void Player::newHand() {
	// the player's hand resets (all current cards are removed)
	m_playerHand.newHand();
}
void Player::setAmount(int money) {
	// the amount in players wallet is set.
	m_money = money;
}
void Player::winAmount(int money) {
	// money is added to players wallet.
	m_money += money;
}
void Player::loseAmount(int money) {
	// money is taken from players wallet.
	m_money -= money;
}
int Player::getAmount() {
	// returns the current amount in players wallet.
	return m_money;
}
void Player::setName(string name) {
	// sets a name for the player.
	m_name = name;
}
string Player::getName() {
	// returns the players name when called.
	return m_name;
}
string Player::getStatus() {
	// returns the pokerhand status of player or high card if only singles.
	return m_playerHand.getStatus();
}
int Player::getStatusID() {
	// statusID is a number used to rank the differences between two pokerhands. ie. Three of a Kind = 3 a Full House = 6; Full House > Three of a Kind.
	return m_playerHand.getStatusID();
}
