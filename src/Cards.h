#include <iostream>
#include <string>

using namespace std;

#ifndef CARDS_H
#define CARDS_H

class Cards {
private:
	int m_face, m_suit; // stores the face and suit of card.

	// represents the corresponding names for the faces and suits as a string
	static string m_faces[13];
	static string m_suits[4];

	// represents the corresponding shortform character symbols for the faces and suits as a string
	static char m_facesChar[13];
	static char m_suitsChar[4];

public:
	Cards();
	Cards(int face, int suit);

	void setFace(int);
	void setSuit(int);

	string getFaceWord();
	string toString();

	int getFace();
	int getSuit();
	int getRank();
	char getFaceChar();
	char getSuitChar();


};

#endif
