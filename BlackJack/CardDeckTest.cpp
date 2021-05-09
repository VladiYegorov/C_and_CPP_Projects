#include "CardDeck.h"
#include "Exceptions.h"
#include "TestMacros.h"

using blackJack::CardDeckIsEmptyException;
using blackJack::CardWrongArgsException;

bool cardDeckConstractorsTest() {
	CardDeck emptyDeck;
	ASSERT_THROW(CardDeckIsEmptyException, emptyDeck.top());
	ASSERT_EQUALS(0, emptyDeck.size());

	CardDeck fullDeck = CardDeck::getFullDeck();
	Card kingSpade = fullDeck.draw();
	ASSERT_EQUALS(kingSpade, Card(Card::Spade, 'K'));
	ASSERT_EQUALS(Card(Card::Spade, 'Q'), fullDeck.top());
	ASSERT_EQUALS(51, fullDeck.size());
	Card queenSpade = fullDeck.draw();
	ASSERT_EQUALS(queenSpade, Card(Card::Spade, 'Q'));
	ASSERT_EQUALS(50, fullDeck.size());

	CardDeck singleCardDeck(Card(Card::Diamond,'J'));
	ASSERT_EQUALS(1, singleCardDeck.size());
	ASSERT_EQUALS(Card(Card::Diamond, 'J'), singleCardDeck.top());

	CardDeck copy1(fullDeck);
	ASSERT_EQUALS(Card(Card::Spade, 'J'), copy1.top());
	ASSERT_EQUALS(50, copy1.size());
	fullDeck.draw();
	ASSERT_EQUALS(Card(Card::Spade, 'J'), copy1.top());
	ASSERT_EQUALS(50, copy1.size());

	CardDeck copy2 = fullDeck;
	ASSERT_EQUALS(Card(Card::Spade, 10), copy2.top());
	ASSERT_EQUALS(49, copy2.size());
	fullDeck.draw();
	ASSERT_EQUALS(Card(Card::Spade, 10), copy2.top());
	ASSERT_EQUALS(49, copy2.size());

	return true;
}

bool drawTopSizeTest() {
	CardDeck fullDeck = CardDeck::getFullDeck();
	ASSERT_EQUALS(52, fullDeck.size());
	ASSERT_EQUALS(Card(Card::Spade, 'K'), fullDeck.top());
	Card kingSpade = fullDeck.draw();
	ASSERT_EQUALS(kingSpade, Card(Card::Spade, 'K'));
	ASSERT_EQUALS(Card(Card::Spade, 'Q'), fullDeck.top());
	ASSERT_EQUALS(51, fullDeck.size());

	Card queenSpade = fullDeck.draw();
	ASSERT_EQUALS(queenSpade, Card(Card::Spade, 'Q'));
	ASSERT_EQUALS(50, fullDeck.size());
	ASSERT_EQUALS(Card(Card::Spade, 'J'), fullDeck.top());

	CardDeck singleCardDeck(Card(Card::Diamond,'J'));
	ASSERT_EQUALS(1, singleCardDeck.size());
	ASSERT_EQUALS(Card(Card::Diamond, 'J'), singleCardDeck.top());
	Card jackDiamond = singleCardDeck.draw();
	ASSERT_EQUALS(jackDiamond, Card(Card::Diamond, 'J'));
	ASSERT_THROW(CardDeckIsEmptyException, singleCardDeck.top());
	ASSERT_EQUALS(0, singleCardDeck.size());

	CardDeck emptyDeck;
	ASSERT_THROW(CardDeckIsEmptyException, emptyDeck.draw());
	ASSERT_THROW(CardDeckIsEmptyException, emptyDeck.top());
	ASSERT_EQUALS(0, emptyDeck.size());

	return true;
}

bool isEmptyClearTest() {
	CardDeck fullDeck = CardDeck::getFullDeck();
	CardDeck emptyDeck;

	ASSERT_EQUALS(true, emptyDeck.isEmpty());
	ASSERT_EQUALS(false, fullDeck.isEmpty());

	fullDeck.clear();
	ASSERT_EQUALS(true, fullDeck.isEmpty());

	return true;
}

bool cardDeckOperatorsTest() {
	CardDeck deck;
	deck += Card(Card::Diamond, 'J') ;
	deck += 3 * Card(Card::Club, 'A') ;
	ASSERT_EQUALS(4, deck.size());
	ASSERT_EQUALS(Card(Card::Club, 'A'), deck.top());

	deck = Card(Card::Diamond, 7) + Card(Card::Diamond, 10);
	ASSERT_EQUALS(2, deck.size());
	ASSERT_EQUALS(Card(Card::Diamond, 10), deck.top());

	deck += 3 * Card(Card::Club, 'A') ;
	ASSERT_EQUALS(5, deck.size());

	CardDeck deck2(Card(Card::Club, 'A'));
	deck2 += Card(Card::Diamond, 7);

	ASSERT_EQUALS(true, deck2 < deck);
	ASSERT_EQUALS(false, deck < deck2);
	ASSERT_EQUALS(false, deck2 > deck);
	ASSERT_EQUALS(true, deck > deck2);

	(deck2 += Card(Card::Diamond, 10)) += Card(Card::Club, 'A') * 2;
	ASSERT_EQUALS(true, deck2 <= deck);
	ASSERT_EQUALS(true, deck <= deck2);
	ASSERT_EQUALS(true, deck2 >= deck);
	ASSERT_EQUALS(true, deck >= deck2);
	ASSERT_EQUALS(true, deck != deck2);
	ASSERT_EQUALS(false, deck == deck2);

	deck2 = Card(Card::Diamond, 7) + Card(Card::Diamond, 10) + 3 *
			Card(Card::Club, 'A');

	ASSERT_EQUALS(false, deck != deck2);
	ASSERT_EQUALS(true, deck == deck2);

	return true;
}

bool valueTest() {
	CardDeck deck;
	(deck += Card(Card::Diamond, 'J')) += Card(Card::Heart, 9);
	deck += 3 * Card(Card::Club, 'A') ;
	ASSERT_EQUALS(5, deck.size());

	unsigned expectedValue = 42;
	ASSERT_EQUALS(expectedValue, deck.value());

	return true;
}

DEFINE_INPUT_TEST(cardDeck)
	CardDeck deck;
	input >> deck;
	ASSERT_EQUALS(3, deck.size());
	ASSERT_EQUALS(Card(Card::Club,4), deck.top());
	std::cout << deck * 2 << std::endl;

	CardDeck first;
	CardDeck second;
	input >> first;
	ASSERT_EQUALS(4, first.size());
	ASSERT_THROW(CardWrongArgsException, input >> second);
	ASSERT_EQUALS(1, second.size());
	std::cout << first + second << std::endl;
	return true;
}

bool cardDeckInputOutputTest() {
	RUN_TEST(cardDeck);
	return true;
}

bool cardDeckTest() {
	RUN_TEST(cardDeckConstractorsTest);
	RUN_TEST(drawTopSizeTest);
	RUN_TEST(isEmptyClearTest);
	RUN_TEST(cardDeckOperatorsTest);
	RUN_TEST(valueTest);
	cardDeckInputOutputTest();
	return true;
}

