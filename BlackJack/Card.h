#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include "Exceptions.h"

using std::string;
using std::istream;
using std::ostream;

class Card {
public:
	enum Suit { Heart, Diamond, Club, Spade };
private:
	Suit suit;
	int value; // the values are from 1 to 13:A=1 ,J=11, Q=12, K=13
public:
	Card();
	Card(Suit suit, int value);
	Card(Suit suit, char identier);
	Card(const Card& card) = default;
	~Card() = default;
	Card& operator=(const Card& card) = default;

	void setSuit(Suit suit);
	void setSuit(const char suit);
	void setValue(const char value);
	void setValue(int value);

	Suit getSuit() const;
	int getValue() const;

	void createCardFromString(const string str);
	bool emptyCard() const;

	friend bool operator==(const Card& card1, const Card& card2);
	friend bool operator!=(const Card& card1, const Card& card2);
	friend ostream& operator<<(ostream& output,const Card& card);
	friend istream& operator>>(istream& input, Card& card);
};

#endif // CARD_H
