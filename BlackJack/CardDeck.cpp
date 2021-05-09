#include "CardDeck.h"
#include <fstream>
using std::istream;
using std::ostream;
using std::endl;
using blackJack::CardDeckIsEmptyException;

static int roundUpper(double num) {
	int round = num;
	if(num == round) {
		return num;
	}
	return (int)num+1;
}

static unsigned int calculateAceOption(unsigned int sum,int numOfAces) {
	double tempSum = sum;
	tempSum += numOfAces;
	int minDiv = roundUpper(tempSum/21);
	for(int i=numOfAces;i>0;i--) {
		if(roundUpper((double)(tempSum+10)/21) == minDiv) {
			tempSum += 10;
		} else {
			break;
		}
	}
	return tempSum;
}


CardDeck::CardDeck() {

}

CardDeck::CardDeck(const Card& card) {
	deck.push_back(card);
}

CardDeck::CardDeck(const CardDeck& deck) {
	if(this == &deck) {
		return;
	}
	this->deck.clear();
	for(unsigned int i=0; i<deck.deck.size(); i++) {
		Card temp(deck.deck[i]);
		this->deck.push_back(temp);
	}
}

CardDeck& CardDeck::operator=(const CardDeck& deck) {
	if(this == &deck) {
		return *this;
	}
	this->deck.clear();
	*this += deck;
	return *this;
}


CardDeck::~CardDeck() {

}

CardDeck CardDeck::getFullDeck() {
	CardDeck full;
	for(int i=0; i<4; i++) {
		Card::Suit tempSuit;
		switch(i) {
			case 0: tempSuit = Card::Heart; break;
			case 1: tempSuit = Card::Diamond; break;
			case 2: tempSuit = Card::Club; break;
			case 3: tempSuit = Card::Spade; break;
		}
		for(int j=1; j<=10; j++) {
			Card tempCard(tempSuit, j);
			full.deck.push_back(tempCard);
		}
		Card tempCard(tempSuit, 'J');
		full.deck.push_back(tempCard);
		tempCard.setValue('Q');
		full.deck.push_back(tempCard);
		tempCard.setValue('K');
		full.deck.push_back(tempCard);

	}
	return full;
}

Card CardDeck::draw() {
	if(!deck.size()) {
		throw CardDeckIsEmptyException();
	}
	Card result = deck[deck.size()-1];
	deck.pop_back();
	return result;
}

Card& CardDeck::top() {
	if(!deck.size()) {
		throw CardDeckIsEmptyException();
	}
	Card& result = deck[deck.size()-1];
	return result;
}

unsigned int CardDeck::size() const{
	return deck.size();
}

bool CardDeck::isEmpty() const {
	if(deck.size() == 0) {
		return true;
	}
	return false;
}

void CardDeck::clear() {
	deck.clear();
}

unsigned int CardDeck::value() const {
	int countAces = 0;
	int sum=0;
	for(unsigned int i=0;i<deck.size();i++) {
		Card temp = deck[i];
		if(temp.getValue() == 1) {
			countAces++;
		}
		if(temp.getValue() >= 2 && temp.getValue() <= 10) {
			sum += temp.getValue();
		}
		if(temp.getValue() >=11 && temp.getValue() <=13) {
			sum += 10;
		}
	}
	if(!countAces) {
		return sum;
	}
	return calculateAceOption(sum,countAces);
}

unsigned int CardDeck::appearsOfAces() const {
	unsigned int result = 0;
	for(unsigned int i=0; i<this->size(); i++) {
		Card it = this->deck[i];
		if(it.getValue() == 1) {
			result++;
		}
	}
	return result;
}

unsigned int CardDeck::appearsInDeck(const Card& card) const {
	unsigned int result = 0;
	for(unsigned int i=0; i<this->size(); i++) {
		Card it = this->deck[i];
		if(card == it) {
			result++;
		}
	}
	return result;
}

CardDeck& CardDeck::operator+=(const CardDeck& deck) {
	for(unsigned int i=0; i<deck.deck.size();i++) {
		Card temp = deck.deck[i];
		this->deck.push_back(temp);
	}
	return *this;
}

CardDeck operator+(const CardDeck& deck1, const CardDeck& deck2) {
	CardDeck result;
	result += deck1;
	result += deck2;
	return result;
}

CardDeck operator*(const CardDeck& deck,unsigned int num) {
	CardDeck result;
	for(unsigned int mul = num;mul>0;mul--) {
		result += deck;
	}
	return result;
}

CardDeck operator*(unsigned int num, const CardDeck& deck) {
	return (deck*num);
}

istream& operator>>(istream& input, CardDeck& deck) {
	string str;
	getline(input,str);
	unsigned int numOfArgs = str[0] - '0';
	int firstIndex = 2;
	int lastIndex = 2;
	for(unsigned int i=0;i<numOfArgs;i++) {
		string tempString;
		while(str[lastIndex] != ' ' && str[lastIndex] != '\0' &&
				str[lastIndex] != '\t' && str[lastIndex] != '\n' ) {
			lastIndex++;
		}
		tempString = str.substr (firstIndex,lastIndex-firstIndex);
		Card tempCard;
		tempCard.createCardFromString(tempString);
		deck.deck.push_back(tempCard);
		lastIndex++;
		firstIndex = lastIndex;
	}
	return input;
}

ostream& operator<<(ostream& output,const CardDeck &deck) {
	output << deck.size() << " ";
	for(unsigned int i=0;i<deck.size();i++) {
		Card temp = deck.deck[i];
		if(i+1 != deck.size()) {
			output << temp << " ";
		} else {
			output << temp;
		}
	}
	return output;
}

bool operator==(const CardDeck& deck1,const CardDeck& deck2) {
	if(deck1.size() != deck2.size()) {
		return false;
	}
	for(unsigned int i=0;i<deck1.size();i++) {
		Card card1Index = deck1.deck[i];
		Card card2Index = deck2.deck[i];
		if(card1Index != card2Index) {
			return false;
		}
	}
	return true;
}

bool operator!=(const CardDeck& deck1,const CardDeck& deck2) {
	if(deck1 == deck2) {
		return false;
	}
	return true;
}

bool operator<=(const CardDeck& deck1,const CardDeck& deck2) {
	if(deck1.size() > deck2.size()) {
		return false;
	}
	for(unsigned int i=0;i<deck1.size();i++) {
		Card temp = deck1.deck[i];
		unsigned int countsInDeck1 = deck1.appearsInDeck(temp);
		unsigned int countsInDeck2 = deck2.appearsInDeck(temp);
		if(countsInDeck1 > countsInDeck2) {
			return false;
		}
	}
	return true;
}

bool operator>=(const CardDeck& deck1,const CardDeck& deck2) {
	return (deck2 <= deck1);
}

bool operator<(const CardDeck& deck1,const CardDeck& deck2) {
	if(deck1 <= deck2) {
		if(deck1 >= deck2) {
			return false;
		}
		return true;
	}
	return false;
}

bool operator>(const CardDeck& deck1,const CardDeck& deck2) {
	return (deck2 < deck1);
}
