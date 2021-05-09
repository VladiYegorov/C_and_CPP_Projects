#ifndef CARDDECK_H_
#define CARDDECK_H_

#include <iostream>
#include <vector>
#include "Card.h"

#define NUM_OF_SUITS 4
#define NUM_OF_VALUES 13

using namespace std;

class CardDeck {
private:
	vector<Card> deck;
public:
	CardDeck();
	CardDeck(const Card& card);
	CardDeck(const CardDeck& deck) ;
	CardDeck& operator=(const CardDeck& deck);
	~CardDeck();

	static CardDeck getFullDeck();
	Card draw();
	Card& top();
	unsigned int size() const;
	bool isEmpty() const;
	void clear();

	unsigned int value() const;

	unsigned int appearsOfAces() const;
	unsigned int appearsInDeck(const Card& card) const;
	CardDeck& operator+=(const CardDeck& deck);

	friend bool operator==(const CardDeck& deck1,const CardDeck& deck2);
	friend bool operator!=(const CardDeck& deck1,const CardDeck& deck2);
	friend bool operator>=(const CardDeck& deck1,const CardDeck& deck2);
	friend bool operator<=(const CardDeck& deck1,const CardDeck& deck2);
	friend bool operator>(const CardDeck& deck1,const CardDeck& deck2);
	friend bool operator<(const CardDeck& deck1,const CardDeck& deck2);

	friend ostream& operator<<(ostream& output,const CardDeck &deck);
	friend istream& operator>>(istream& input, CardDeck& deck);
};

CardDeck operator+(const CardDeck& deck1, const CardDeck& deck2);
CardDeck operator*(const CardDeck& deck,unsigned int num);
CardDeck operator*(unsigned int num, const CardDeck& deck);

#endif /* CARDDECK_H_ */
