#include "Card.h"
#include "Exceptions.h"
#include "TestMacros.h"

using blackJack::CardWrongArgsException;
using std::string;

bool cardConstractorsTest() {
	ASSERT_THROW(CardWrongArgsException, Card(Card::Spade, -1));
	ASSERT_THROW(CardWrongArgsException, Card(Card::Spade, 0));
	ASSERT_THROW(CardWrongArgsException, Card(Card::Spade, 11));
	ASSERT_THROW(CardWrongArgsException, Card(Card::Spade, 'P'));

	Card card1(Card::Club, 2);
	ASSERT_EQUALS(2, card1.getValue());
	ASSERT_EQUALS(Card::Club, card1.getSuit());

	Card card2(Card::Diamond, 'K');
	ASSERT_EQUALS(13, card2.getValue());
	ASSERT_EQUALS(Card::Diamond, card2.getSuit());

	Card card3 = card1;
	ASSERT_EQUALS(2, card3.getValue());
	ASSERT_EQUALS(Card::Club, card3.getSuit());

	Card card4;
	ASSERT_EQUALS(0, card4.getValue());
	ASSERT_EQUALS(Card::Heart, card4.getSuit());

	Card card5(card2);
	ASSERT_EQUALS(13, card5.getValue());
	ASSERT_EQUALS(Card::Diamond, card5.getSuit());
	card2.setValue('J');
	ASSERT_EQUALS(11, card2.getValue());
	ASSERT_EQUALS(13, card5.getValue());

	return true;
}

bool setersGetersTest() {
	Card card(Card::Diamond, 'K');
	ASSERT_EQUALS(13, card.getValue());
	ASSERT_EQUALS(Card::Diamond, card.getSuit());

	card.setValue(5);
	card.setSuit(Card::Club);
	ASSERT_EQUALS(5, card.getValue());
	ASSERT_EQUALS(Card::Club, card.getSuit());

	ASSERT_THROW(CardWrongArgsException, card.setValue(11));
	ASSERT_THROW(CardWrongArgsException, card.setValue(0));
	ASSERT_THROW(CardWrongArgsException, card.setSuit('P'));

	card.setValue('q');
	card.setSuit('d');
	ASSERT_EQUALS(12, card.getValue());
	ASSERT_EQUALS(Card::Diamond, card.getSuit());

	return true;
}

bool createCardFromStringTest () {
	string str1 = "kD";
	string str2 = "10c";
	string str3 = "kd";
	string str4 = "5HC";
	string str5 = "ab";
	string str6 = "5SC";

	Card card;
	card.createCardFromString(str1);
	ASSERT_EQUALS(13, card.getValue());
	ASSERT_EQUALS(Card::Diamond, card.getSuit());

	card.createCardFromString(str2);
	ASSERT_EQUALS(10, card.getValue());
	ASSERT_EQUALS(Card::Club, card.getSuit());

	card.createCardFromString(str3);
	ASSERT_EQUALS(13, card.getValue());
	ASSERT_EQUALS(Card::Diamond, card.getSuit());

	ASSERT_THROW(CardWrongArgsException,card.createCardFromString(str4));
	ASSERT_THROW(CardWrongArgsException,card.createCardFromString(str5));
	ASSERT_THROW(CardWrongArgsException,card.createCardFromString(str6));

	return true;
}

bool emptyCard() {
	Card card;
	ASSERT_EQUALS(true, card.emptyCard());
	card.setSuit('S');
	ASSERT_EQUALS(true, card.emptyCard());
	card.setValue(1);
	ASSERT_EQUALS(false, card.emptyCard());

	return true;
}

bool cardOperatorsTest() {
	Card card1(Card::Club, 10);
	Card card2;
	ASSERT_EQUALS(false, card1 == card2);
	ASSERT_EQUALS(true, card1 != card2);

	card2.setSuit('C');
	ASSERT_EQUALS(false, card1 == card2);
	ASSERT_EQUALS(true, card1 != card2);

	card2.setValue(10);
	ASSERT_EQUALS(true, card1 == card2);
	ASSERT_EQUALS(false, card1 != card2);

	return true;
}

DEFINE_INPUT_TEST(card)
	Card card1(Card::Club, 10);
	Card card2(Card::Diamond,'K');
	Card card3;
	Card card4;
	input >> card3;
	ASSERT_THROW(CardWrongArgsException,input >> card3);
	input >> card4;
	ASSERT_EQUALS(true, card1 == card3);
	ASSERT_EQUALS(true, card2 == card4);

	return true;
}


bool cardInputTest() {
	RUN_TEST(card);
	return true;
}


bool cardTest() {
	RUN_TEST(cardConstractorsTest);
	RUN_TEST(setersGetersTest);
	RUN_TEST(createCardFromStringTest);
	RUN_TEST(emptyCard);
	RUN_TEST(cardOperatorsTest);
	cardInputTest();
	return true;
}



