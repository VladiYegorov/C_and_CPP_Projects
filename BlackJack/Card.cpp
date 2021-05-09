#include "Card.h"
using namespace blackJack;
using std::string;

static int convertIdentierToInt(const char identier) {
	switch(identier) {
		case 'a': return 1;
		case 'A': return 1;
		case 'j': return 11;
		case 'J': return 11;
		case 'q': return 12;
		case 'Q': return 12;
		case 'k': return 13;
		case 'K': return 13;
	}
	if(identier - '0' >= 2 && identier - '0' <= 10) {
		return (identier - '0');
	}
	throw CardWrongArgsException();
}

static char convertIntToIdentier(int value) {
	switch(value) {
		//case '1': return 'A';
		case 11: return 'J';
		case 12: return 'Q';
		case 13: return 'K';
		default: throw CardWrongArgsException();
	}
}

static void legitIntValue(int value) {
	if(value <= 0 || value>= 11) {
		throw CardWrongArgsException();
	}
}

static void legitCharValue(const char value) {
	convertIdentierToInt(value);
}

static Card::Suit convertCharToSuit(const char suit) {
	switch(suit) {
		case 'H': return Card::Heart;
		case 'h': return Card::Heart;
		case 'D': return Card::Diamond;
		case 'd': return Card::Diamond;
		case 'C': return Card::Club;
		case 'c': return Card::Club;
		case 'S': return Card::Spade;
		case 's': return Card::Spade;
		default: throw CardWrongArgsException();
	}
}

static char convertSuitToChar(Card::Suit suit) {
	switch(suit) {
	case Card::Heart: return 'H';
	case Card::Diamond: return 'D';
	case Card::Club: return 'C';
	case Card::Spade: return 'S';
	default: throw CardWrongArgsException();
	}
}

Card::Card() {
	suit = Heart;
	value = 0;
}

Card::Card(Suit suit, int value) {
	legitIntValue(value);
	this->suit = suit;
	this->value = value;
}

Card::Card(Suit suit, char identier) {
	int identierToInt = convertIdentierToInt(identier);
	this->suit = suit;
	this->value = identierToInt;
}

void Card::setSuit(Suit suit) {
	this->suit = suit;
}

void Card::setSuit(const char suit) {
	this->suit = convertCharToSuit(suit);
}

void Card::setValue(char value) {
	legitCharValue(value);
	this->value = convertIdentierToInt(value);
}

void Card::setValue(int value) {
	legitIntValue(value);
	this->value = value;
}

Card::Suit Card::getSuit() const {
	return suit;
}
int Card::getValue() const {
	return value;
}

void Card::createCardFromString(const string str) {
	if(str.size() != 2 && str.size() != 3) {
		throw CardWrongArgsException();
	}
	if(str.size() == 2) {
		this->setValue(str[0]);
		this->setSuit(str[1]);
		return;
	}
	if(str[0] != '1' || str[1] != '0') {
		throw CardWrongArgsException();
	}
	this->setValue(10);
	this->setSuit(str[2]);
}

bool Card::emptyCard() const {
	if(value == 0) {
		return true;
	}
	return false;
}


ostream& operator<<(ostream& output,const Card& card) {
	if(!card.getValue()) {
		output << "";
	}
	if(card.getValue() <= 10) {
		return output << card.getValue() << convertSuitToChar(card.getSuit());
	}
	return output << convertIntToIdentier(card.getValue()) <<
				convertSuitToChar(card.getSuit());
}

istream& operator>>(istream& input, Card& card) {
	string str;
	getline(input,str);
	card.createCardFromString(str);
	return input;
}

bool operator==(const Card& card1, const Card& card2) {
	if(card1.suit == card2.suit && card1.value == card2.value) {
		return true;
	}
	return false;
}

bool operator!=(const Card& card1, const Card& card2) {
	if(card1 == card2) {
		return false;
	}
	return true;
}


