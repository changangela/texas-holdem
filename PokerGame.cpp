#include <iostream>

#include <ctime>
#include <cstdlib>

#include "PokerGame.h"

using namespace std;

void PokerGame::pauseScreen() {
	// this function is called when pausing the screen.
	// prompts user to press enter to continue.
	cout << "Press Enter to continue..." << endl;
	cin.ignore();
}
void PokerGame::printInfo() {
	// displays current statistics in a table.

	const int TABLE_SIZE = 16; // each column is set to 16 characters long.

	string m_playerMoney, computerMoney, m_currentPotMoney;

	// the player name/money, computer name/money, and pot name/money are displayed side by side.
	m_playerMoney = "$" + m_player.getAmount();
	computerMoney = "$" + m_cpuAI.getAmount();
	m_currentPotMoney = "$" + m_currentPot;

	cout << m_player.getName() << ":"
			<< string(TABLE_SIZE - m_player.getName().length() - 1, ' ')
			<< "Computer:" << string(TABLE_SIZE - 9, ' ') << "Pot:"
			<< string(TABLE_SIZE - 4, ' ') << "\n";
	cout << "$" << m_player.getAmount() << "\t \t$" << m_cpuAI.getAmount()
			<< "\t \t$" << m_currentPot;
}
void PokerGame::Round1() {
	// this function generates the first round of the game.

	cout << "--------------- ROUND 1 --------------\n\n";

	// the dealer and players reset.
	// the dealer obtains a new deck and shuffles the cards.
	m_player.newHand();
	m_cpuAI.newHand();
	m_dealer.newDeck();

	// each player starts by paying 10$ to the currentPot.
	m_currentBet = COST;
	m_player.loseAmount(COST);
	m_cpuAI.loseAmount(COST);
	m_currentPot = COST * 2;

	// information is displayed to the console.
	printInfo();

	// the dealer deals both the player and the computer 2 cards each.
	m_player.dealCard(m_dealer, 2);
	m_cpuAI.dealCard(m_dealer, 2);

	// players hand is printed to screen.
	cout << "\n\nHand:";
	m_player.printHand();

	// player action is performed here.
	playerAction();

	// computer action is performed here.
	computerAction();

	RoundN();
}
void PokerGame::RoundN() {
	// similar to Round1, however this includes the all the rounds afterwards should they occur.

	// for loop that runs from round 2 to round 4.
	for (int i = 2; i < 5; i++) {

		//each round, the bet and amounts are reset.
		// the pot was not reset.
		m_currentBet = 0;
		m_currentAmount = 0;

		// if the game is not over, the following actions proceed.
		if (!m_gameOver) {

			cout << "\n\n--------------- ROUND " << i << " --------------\n\n";
			printInfo();

			// The dealer deals both the player and the computer 1 card each round.
			m_player.dealCard(m_dealer, 1);
			m_cpuAI.dealCard(m_dealer, 1);

			// the players hand is printed to screen.
			cout << "\n\n" << m_player.getName() << "'s Hand:";
			m_player.printHand();

			// the order of player/computer action alternates with each round.
			playerAction();

			// if the player did not choose to fold, the game proceeds.
			if (!m_gameOver) {
				computerAction();
				if (i == 4) {
					compare();
				}
			}
		}
	}
}
void PokerGame::restart() {
	// after the game is over, this function prompts to play new hand.

	if (m_player.getAmount() >= 10) {
		// if the player has more than $10, he can afford to play a new round.

		if (m_cpuAI.getAmount() >= 10) {
			// if the computer has more than $10, he can afford to play a new round.

			// the player chooses if they want to be dealt a new hand.
			cout << "New hand? [y/n]: ";
			char choice = ' ';
			while (!((choice == 'y') | (choice == 'n'))) {
				cin >> choice;
			}
			cout << endl;

			if (choice == 'y') {
				// the game restarts if a new hand was chosen.
				m_gameOver = false;
				Round1();
			}
		} else {
			cout << "Computer is out of money...";
		}
	} else {
		cout << m_player.getName() << " is out of money...";
	}

}
void PokerGame::compare() {
	// this function displays both player and computers hands and judges the winner.

	// the status determines the pokerhand or otherwise high card.
	cout << "\n" << m_player.getName() << "'s Hand:";
	m_player.printHand();
	cout << m_player.getStatus() << endl;

	cout << "\nComputer Hand:";
	m_cpuAI.printHand();
	cout << m_cpuAI.getStatus() << endl << endl;

	// the winner wins the pot amount.
	if (m_player.getStatusID() > m_cpuAI.getStatusID()) {
		cout << m_player.getName() << " wins $" << m_currentPot << "...\n\n";
		m_player.winAmount(m_currentPot);
	} else {
		cout << "Computer wins $" << m_currentPot << "...\n\n";
		m_cpuAI.winAmount(m_currentPot);
	}

	// the restart function is called.
	m_gameOver = true;
	restart();

}
void PokerGame::flop(Player &p_player, Player &p_other) {
	// this function defines the folding action.

	// the game is over.
	m_gameOver = true;

	// the opposing play wins the pot.
	cout << p_player.getName() << " folds...\n\n";
	cout << p_other.getName() << " wins $" << m_currentPot << "...\n\n";
	p_other.winAmount(m_currentPot);

	// the game restarts.
	restart();
}
void PokerGame::call(Player &p_player) {
	// this function defines the calling action.

	cout << p_player.getName() << " calls...\n\n";

	// the player loses the amount raised by others should he choose to call.
	p_player.loseAmount(m_currentAmount);
	m_currentPot += m_currentAmount;
}
void PokerGame::raisePlayer() {

	// this function defines the action of a player raising.

	// the player selects the amount he wishes to raise the stakes by.
	int amount;
	cout << "Amount raised by: ";
	cin >> amount;

	// if there is insufficient amount in the players wallet, the action would automatically put all in.
	if (amount > m_player.getAmount()) {
		cout << "All in!\n";
		amount = m_player.getAmount();
	}

	// the player loses chosen raised amount.
	m_currentAmount = amount;
	m_currentBet += amount;
	m_player.loseAmount(amount);
	m_currentPot += amount;
	cout << m_player.getName() << " raises by $" << amount << "...\n\n";
}
void PokerGame::raiseComputer() {
	// this function defines the actions of a computer raising.

	// the computer must first pay the set cost or previously raised amount.
	m_cpuAI.loseAmount(m_currentAmount);

	// the amount the computer raises by is a random number between 1 and computer wallet total.
	int amount = rand() % m_cpuAI.getAmount() + 1;

	// the amount is then deducted from computer wallet.
	m_currentAmount = amount;
	m_currentBet += amount;
	m_cpuAI.loseAmount(amount);
	m_currentPot += amount;
	cout << m_cpuAI.getName() << " raises by $" << amount << "...\n";

	// the player is then prompted to either call or fold on the computers raised amount.
	cout << "Action: call $" << amount << "[c]/fold[f]: ";
	char action = ' ';
	while (!((action == 'c') || (action == 'f'))) {
		cin >> action;
	}
	cout << endl;

	// the players action is propagated here.
	switch (action) {
	case 'c':
		call(m_player);
		break;
	default:
		flop(m_player, m_cpuAI);
	}
}
void PokerGame::playerAction() {
	// this function is called on every player turn.

	// current information is displayed.
	cout << "Current bet: $" << m_currentBet << endl;
	cout << "Action: call[c]/raise[r]/fold[f]: ";

	// the player is prompted to either call, fold, or raise.
	char action = ' ';
	while (!((action == 'c') | (action == 'r') | (action == 'f'))) {
		cin >> action;
	}
	cout << endl;
	switch (action) {
	case 'c':
		call(m_player);
		break;
	case 'r':
		raisePlayer();
		break;
	default:
		flop(m_player, m_cpuAI);
	}
}
void PokerGame::computerAction() {
	// this functions defines the computers actions.

	// the computer must either call, raise, or fold.
	// the computer's actions is randomly generated.
	// 10% chance of folding, 30% chance of raising, 60% chance of calling.
	int randomAction = rand() % 10;
	switch (randomAction) {
	case 0:
		flop(m_cpuAI, m_player);
		break;
	case (1 || 2 || 3):
		raiseComputer();
		break;
	default:
		call(m_cpuAI);
	}
}

PokerGame::PokerGame() {
	// this constructor method sets initializers for variables.
	m_currentPot = 0;
	m_currentBet = COST;
	m_currentAmount = COST;
	m_gameOver = false;
}
void PokerGame::initialize() {
	// this public function is called from instances of the class to begin the poker game.

	cout << "------------" << " POKER GAME " << "------------" << endl;

	// the user inputs names.
	string name;
	cout << "Name: ";
	getline(cin, name);
	m_player.setName(name);

	cout << "\nWelcome " << m_player.getName()
			<< "! Your poker game is about to begin.\n";
	pauseScreen();

	//-----------------------------------------------

	// the game starts with Round1.
	Round1();
}

